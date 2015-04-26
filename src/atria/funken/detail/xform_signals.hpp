// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/signals.hpp>
#include <atria/funken/detail/no_value.hpp>
#include <atria/xform/transducers.hpp>
#include <atria/xform/reducers.hpp>
#include <atria/estd/utility.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace funken {

namespace detail {

//!
// Metafunction that returns the value type for a signal based on
// transducer `XForm` when inputed values from sources
// `Sources`. `Sources` must have a `Value_type<>`.
//
template <typename XForm, typename ...Sources>
struct get_xform_result
{
  using type = estd::decay_t<
    decltype(
      std::declval<XForm>()(xform::last_r)(
        std::declval<detail::no_value>(),
        std::declval<estd::Value_type<Sources> >()...))
    >;
};

template <typename XForm, typename ...Parents>
using get_xform_result_t =
  typename get_xform_result<XForm, Parents...>::type;

constexpr struct
{
  template <typename DownSignalPtr, typename ...Inputs>
  auto operator () (DownSignalPtr s, Inputs&& ...is) const
    -> DownSignalPtr
  {
    s->push_down(xform::tuplify(std::forward<Inputs>(is)...));
    return s;
  }

  template <typename DownSignalPtr, typename ...Inputs>
  auto operator () (DownSignalPtr s) const
    -> DownSignalPtr
  {
    return s;
  }
} send_down_r {};


template <typename T, typename Err>
auto default_construct_or_throw()
  -> estd::enable_if_t<std::is_default_constructible<T>::value, T>
{
  return T();
}

template <typename T, typename Err>
auto default_construct_or_throw()
  -> estd::enable_if_t<!std::is_default_constructible<T>::value, T>
{
  throw Err();
}

//!
// Implementation of a signal with a transducer.
//
template <typename XForm            = decltype(xform::identity),
          typename ParentsPack      = meta::pack<>,
          template<class>class Base = down_signal>
class xform_down_signal;

template <typename XForm,
          typename ...Parents,
          template<class>class Base>
class xform_down_signal<XForm, meta::pack<Parents...>, Base>
  : public Base<get_xform_result_t<XForm, Parents...> >
{
  using base_t = Base<get_xform_result_t<XForm, Parents...> >;
  using down_reducer_t = decltype(std::declval<XForm>()(send_down_r));

  std::tuple<std::shared_ptr<Parents>...> parents_;

public:
  using value_type = typename base_t::value_type;

  xform_down_signal(xform_down_signal&&) = default;
  xform_down_signal(const xform_down_signal&) = delete;
  xform_down_signal& operator=(xform_down_signal&&) = default;
  xform_down_signal& operator=(const xform_down_signal&) = delete;

  template <typename XForm2>
  xform_down_signal(XForm2&& xform, std::shared_ptr<Parents> ...parents)
    : base_t([&]() -> value_type {
        try {
          return xform(xform::last_r)(detail::no_value{}, parents->current()...);
        }
        catch (const no_value_error&) {
          return default_construct_or_throw<value_type, no_value_error>();
        }
      }())
    , parents_(std::move(parents)...)
    , down_reducer_(xform(send_down_r))
  {
  }

  void recompute() final
  { recompute(estd::make_index_sequence<sizeof...(Parents)>{}); }

  void recompute_deep() final
  { recompute_deep(estd::make_index_sequence<sizeof...(Parents)>{}); }

  std::tuple<std::shared_ptr<Parents>...>& parents()
  { return parents_; }
  const std::tuple<std::shared_ptr<Parents>...>& parents() const
  { return parents_; }

private:
  template <std::size_t ...Indices>
  void recompute(estd::index_sequence<Indices...>)
  {
    down_reducer_(this, std::get<Indices>(parents_)->current()...);
  }

  template <std::size_t ...Indices>
  void recompute_deep(estd::index_sequence<Indices...>)
  {
    meta::noop(
      (std::get<Indices>(parents_)->recompute_deep(),
       meta::can_be_void)...);
    recompute();
  }

  down_reducer_t down_reducer_;
};


//!
// Reducer that pushes the received values into the signal that is
// passed as pointer as an accumulator.
//
constexpr struct
{
  template <typename UpSignalPtr, typename ...Inputs>
  auto operator () (UpSignalPtr s, Inputs&& ...is) const
    -> UpSignalPtr
  {
    s->push_up(xform::tuplify(std::forward<Inputs>(is)...));
    return s;
  }
} send_up_r {};

//!
// @see update()
//
struct update_reducer
{
  template <typename ReducerT, typename UpdateT>
  struct apply
  {
    ReducerT reducer;
    UpdateT updater;

    template <typename XformUpSignalPtr, typename ...Inputs>
    auto operator () (XformUpSignalPtr s, Inputs&& ...is) const
      -> XformUpSignalPtr
    {
      auto indices = estd::make_index_sequence<
        std::tuple_size<estd::decay_t<decltype(s->parents())> >::value > {};
      return reducer(s, updater(peek_parents(s, indices),
                                std::forward<Inputs>(is)...));
    }

    template <typename XformUpSignalPtr, std::size_t ...Indices>
    auto peek_parents(XformUpSignalPtr s, estd::index_sequence<Indices...>) const
      -> decltype(xform::tuplify(std::get<Indices>(s->parents())->current()...))
    {
      s->recompute_deep();
      return xform::tuplify(std::get<Indices>(s->parents())->current()...);
    }
  };
};

//!
// Returns a transducer for updating the parent values via a
// up-signal. It processes the input with the function `mapping`,
// passing to it a value or tuple containing the values of the parents
// of the signal as first parameter, and the input as second.  This
// mapping can thus return an *updated* version of the values in the
// parents with the new input.
//
// @note This transducer should only be used for the setter of
// output signals.
//
template <typename UpdateT>
auto update(UpdateT&& updater)
  -> xform::detail::transducer_impl<update_reducer, estd::decay_t<UpdateT> >
{
  return std::forward<UpdateT>(updater);
}

//!
// Implementation of a signal with a transducer
//
template <typename XForm            = decltype(xform::identity),
          typename SetXForm         = decltype(xform::identity),
          typename ParentsPack      = meta::pack<>,
          template<class>class Base = up_down_signal>
class xform_up_down_signal;

template <typename XForm,
          typename SetXForm,
          typename ...Parents,
          template<class>class Base>
class xform_up_down_signal<XForm, SetXForm, meta::pack<Parents...>, Base>
  : public xform_down_signal<XForm, meta::pack<Parents...>, Base>
{
  using base_t = xform_down_signal<XForm, meta::pack<Parents...>, Base>;
  using up_reducer_t = decltype(std::declval<SetXForm>()(send_up_r));

public:
  using value_type = typename base_t::value_type;

  xform_up_down_signal(xform_up_down_signal&&) = default;
  xform_up_down_signal(const xform_up_down_signal&) = delete;
  xform_up_down_signal& operator=(xform_up_down_signal&&) = default;
  xform_up_down_signal& operator=(const xform_up_down_signal&) = delete;

  template <typename XForm2, typename SetXForm2>
  xform_up_down_signal(XForm2&& xform,
                       SetXForm2&& set_xform,
                       std::shared_ptr<Parents> ...parents)
    : base_t(std::forward<XForm2>(xform), std::move(parents)...)
    , up_reducer_(set_xform(send_up_r))
  {}

  void send_up(const value_type& value) final
  {
    send_up(value,
            estd::make_index_sequence<sizeof...(Parents)>{});
  }

  void send_up(value_type&& value) final
  {
    send_up(std::move(value),
            estd::make_index_sequence<sizeof...(Parents)>{});
  }

  template <typename T>
  void push_up(T&& value)
  {
    push_up(std::forward<T>(value),
            estd::make_index_sequence<sizeof...(Parents)>{});
  }

private:
  template <typename T, std::size_t... Indices>
  void send_up(T&& x, estd::index_sequence<Indices...>)
  {
    up_reducer_(this, std::forward<T>(x));
  }

  template <typename T, std::size_t ...Indices>
  void push_up(T&& value, estd::index_sequence<Indices...>)
  {
    auto& parents = this->parents();
    meta::noop(
      (std::get<Indices>(parents)->send_up(
        std::get<Indices>(std::forward<T>(value))),
       meta::can_be_void)...);
  }

  template <typename T>
  void push_up(T&& value, estd::index_sequence<0>)
  {
    std::get<0>(this->parents())->send_up(std::forward<T>(value));
  }

  up_reducer_t up_reducer_;
};


//!
// Links a signal to its parents and returns it.
//
template <typename SignalT>
auto link_to_parents(std::shared_ptr<SignalT> signal)
  -> std::shared_ptr<SignalT>
{
  return link_to_parents(
    std::move(signal),
    estd::make_index_sequence<std::tuple_size<
      estd::decay_t<decltype(signal->parents())>
    >::value>{});
}

template <typename SignalT, std::size_t ...Indices>
auto link_to_parents(std::shared_ptr<SignalT> signal,
                     estd::index_sequence<Indices...>)
  -> std::shared_ptr<SignalT>
{
  auto& parents = signal->parents();
  meta::noop(
    (std::get<Indices>(parents)->link(signal),
     meta::can_be_void)...);
  return signal;
}


//!
// Make a xform_down_signal with deduced types.
//
template <typename XForm, typename ...Parents>
auto make_xform_down_signal(XForm&& xform,
                            std::shared_ptr<Parents> ...parents)
  -> std::shared_ptr<
    xform_down_signal<estd::decay_t<XForm>,
                      meta::pack<Parents...> >
    >
{
  using signal_t = xform_down_signal<estd::decay_t<XForm>,
                                     meta::pack<Parents...> >;
  return link_to_parents(
    std::make_shared<signal_t>(std::forward<XForm>(xform),
                               std::move(parents)...));
}

//!
// Make a xform_down_signal with deduced types.
//
template <typename XForm,
          typename SetXForm,
          typename ...Parents>
auto make_xform_up_down_signal(XForm&& xform,
                               SetXForm&& set_xform,
                               std::shared_ptr<Parents> ...parents)
  -> std::shared_ptr<
    xform_up_down_signal<estd::decay_t<XForm>,
                         estd::decay_t<SetXForm>,
                         meta::pack<Parents...> >
    >
{
  using signal_t = xform_up_down_signal<estd::decay_t<XForm>,
                                        estd::decay_t<SetXForm>,
                                        meta::pack<Parents...> >;
  return link_to_parents(
    std::make_shared<signal_t>(std::forward<XForm>(xform),
                               std::forward<SetXForm>(set_xform),
                               std::move(parents)...));
}

} // namespace detail

} // namespace funken
} // namespace atria
