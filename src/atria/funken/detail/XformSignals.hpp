// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/Signals.hpp>
#include <atria/funken/detail/NoValue.hpp>
#include <atria/xform/Transducers.hpp>
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
struct GetXformResult
{
  using type = estd::decay_t<
    decltype(
      std::declval<XForm>()(xform::lastR)(
        std::declval<detail::NoValue>(),
        std::declval<estd::Value_type<Sources> >()...))
    >;
};

template <typename XForm, typename ...Parents>
using GetXformResult_t =
  typename GetXformResult<XForm, Parents...>::type;

constexpr struct
{
  template <typename DownSignalPtr, typename ...Inputs>
  auto operator () (DownSignalPtr s, Inputs&& ...is) const
    -> DownSignalPtr
  {
    s->pushDown(xform::tuplify(std::forward<Inputs>(is)...));
    return s;
  }

  template <typename DownSignalPtr, typename ...Inputs>
  auto operator () (DownSignalPtr s) const
    -> DownSignalPtr
  {
    return s;
  }
} sendDownR {};


template <typename T, typename Err>
auto defaultConstructOrThrow()
  -> estd::enable_if_t<std::is_default_constructible<T>::value, T>
{
  return T();
}

template <typename T, typename Err>
auto defaultConstructOrThrow()
  -> estd::enable_if_t<!std::is_default_constructible<T>::value, T>
{
  throw Err();
}

//!
// Implementation of a signal with a transducer.
//
template <typename XForm            = decltype(xform::identity),
          typename ParentsPack      = meta::pack<>,
          template<class>class Base = DownSignal>
class XformDownSignal;

template <typename XForm,
          typename ...Parents,
          template<class>class Base>
class XformDownSignal<XForm, meta::pack<Parents...>, Base>
  : public Base<GetXformResult_t<XForm, Parents...> >
{
  using BaseT = Base<GetXformResult_t<XForm, Parents...> >;
  using DownReducerT = decltype(std::declval<XForm>()(sendDownR));

  std::tuple<std::shared_ptr<Parents>...> mParents;

public:
  using value_type = typename BaseT::value_type;

  XformDownSignal(XformDownSignal&&) = default;
  XformDownSignal(const XformDownSignal&) = delete;
  XformDownSignal& operator=(XformDownSignal&&) = default;
  XformDownSignal& operator=(const XformDownSignal&) = delete;

  template <typename XForm2>
  XformDownSignal(XForm2&& xform, std::shared_ptr<Parents> ...parents)
    : BaseT([&]() -> value_type {
        try {
          return xform(xform::lastR)(detail::NoValue{}, parents->current()...);
        }
        catch (const NoValueError&) {
          return defaultConstructOrThrow<value_type, NoValueError>();
        }
      }())
    , mParents(std::move(parents)...)
    , mDownReducer(xform(sendDownR))
  {
  }

  void recompute() final
  { recompute(estd::make_index_sequence<sizeof...(Parents)>{}); }

  void recomputeDeep() final
  { recomputeDeep(estd::make_index_sequence<sizeof...(Parents)>{}); }

  std::tuple<std::shared_ptr<Parents>...>& parents()
  { return mParents; }
  const std::tuple<std::shared_ptr<Parents>...>& parents() const
  { return mParents; }

private:
  template <std::size_t ...Indices>
  void recompute(estd::index_sequence<Indices...>)
  {
    mDownReducer(this, std::get<Indices>(mParents)->current()...);
  }

  template <std::size_t ...Indices>
  void recomputeDeep(estd::index_sequence<Indices...>)
  {
    meta::noop(
      (std::get<Indices>(mParents)->recomputeDeep(),
       meta::can_be_void)...);
    recompute();
  }

  DownReducerT mDownReducer;
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
    s->pushUp(xform::tuplify(std::forward<Inputs>(is)...));
    return s;
  }
} sendUpR {};

//!
// @see update()
//
struct UpdateReducer
{
  template <typename ReducerT, typename UpdateT>
  struct Reducer
  {
    ReducerT reducer;
    UpdateT updater;

    template <typename XformUpSignalPtr, typename ...Inputs>
    auto operator () (XformUpSignalPtr s, Inputs&& ...is) const
      -> XformUpSignalPtr
    {
      auto indices = estd::make_index_sequence<
        std::tuple_size<estd::decay_t<decltype(s->parents())> >::value > {};
      return reducer(s, updater(peekParents(s, indices),
                                std::forward<Inputs>(is)...));
    }

    template <typename XformUpSignalPtr, std::size_t ...Indices>
    auto peekParents(XformUpSignalPtr s, estd::index_sequence<Indices...>) const
      -> decltype(xform::tuplify(std::get<Indices>(s->parents())->current()...))
    {
      s->recomputeDeep();
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
  -> xform::detail::Transducer<UpdateReducer, estd::decay_t<UpdateT> >
{
  return std::forward<UpdateT>(updater);
}

//!
// Implementation of a signal with a transducer.
//
template <typename XForm            = decltype(xform::identity),
          typename SetXForm         = decltype(xform::identity),
          typename ParentsPack      = meta::pack<>,
          template<class>class Base = UpDownSignal>
class XformUpDownSignal;

template <typename XForm,
          typename SetXForm,
          typename ...Parents,
          template<class>class Base>
class XformUpDownSignal<XForm, SetXForm, meta::pack<Parents...>, Base>
  : public XformDownSignal<XForm, meta::pack<Parents...>, Base>
{
  using BaseT = XformDownSignal<XForm, meta::pack<Parents...>, Base>;
  using UpReducerT = decltype(std::declval<SetXForm>()(sendUpR));

public:
  using value_type = typename BaseT::value_type;

  XformUpDownSignal(XformUpDownSignal&&) = default;
  XformUpDownSignal(const XformUpDownSignal&) = delete;
  XformUpDownSignal& operator=(XformUpDownSignal&&) = default;
  XformUpDownSignal& operator=(const XformUpDownSignal&) = delete;

  template <typename XForm2, typename SetXForm2>
  XformUpDownSignal(XForm2&& xform,
                  SetXForm2&& setXform,
                  std::shared_ptr<Parents> ...parents)
    : BaseT(std::forward<XForm2>(xform), std::move(parents)...)
    , mUpReducer(setXform(sendUpR))
  {}

  void sendUp(const value_type& value) final
  {
    sendUp(value,
           estd::make_index_sequence<sizeof...(Parents)>{});
  }

  void sendUp(value_type&& value) final
  {
    sendUp(std::move(value),
           estd::make_index_sequence<sizeof...(Parents)>{});
  }

  template <typename T>
  void pushUp(T&& value)
  {
    pushUp(std::forward<T>(value),
           estd::make_index_sequence<sizeof...(Parents)>{});
  }

private:
  template <typename T, std::size_t... Indices>
  void sendUp(T&& x, estd::index_sequence<Indices...>)
  {
    mUpReducer(this, std::forward<T>(x));
  }

  template <typename T, std::size_t ...Indices>
  void pushUp(T&& value, estd::index_sequence<Indices...>)
  {
    auto& parents = this->parents();
    meta::noop(
      (std::get<Indices>(parents)->sendUp(
        std::get<Indices>(std::forward<T>(value))),
       meta::can_be_void)...);
  }

  template <typename T>
  void pushUp(T&& value, estd::index_sequence<0>)
  {
    std::get<0>(this->parents())->sendUp(std::forward<T>(value));
  }

  UpReducerT mUpReducer;
};


//!
// Links a signal to its parents and returns it.
//
template <typename SignalT>
auto linkToParents(std::shared_ptr<SignalT> pSignal)
  -> std::shared_ptr<SignalT>
{
  return linkToParents(
    std::move(pSignal),
    estd::make_index_sequence<std::tuple_size<
      estd::decay_t<decltype(pSignal->parents())>
    >::value>{});
}

template <typename SignalT, std::size_t ...Indices>
auto linkToParents(std::shared_ptr<SignalT> pSignal,
                   estd::index_sequence<Indices...>)
  -> std::shared_ptr<SignalT>
{
  auto& parents = pSignal->parents();
  meta::noop(
    (std::get<Indices>(parents)->link(pSignal),
     meta::can_be_void)...);
  return pSignal;
}


//!
// Make a XformDownSignal with deduced types.
//
template <typename XForm, typename ...Parents>
auto makeXformDownSignal(XForm&& xform,
                         std::shared_ptr<Parents> ...parents)
  -> std::shared_ptr<
    XformDownSignal<estd::decay_t<XForm>,
                    meta::pack<Parents...> >
    >
{
  using SignalT = XformDownSignal<estd::decay_t<XForm>,
                                  meta::pack<Parents...> >;
  return linkToParents(
    std::make_shared<SignalT>(std::forward<XForm>(xform),
                              std::move(parents)...));
}

//!
// Make a XformDownSignal with deduced types.
//
template <typename XForm,
          typename SetXForm,
          typename ...Parents>
auto makeXformUpDownSignal(XForm&& xform,
                           SetXForm&& setXform,
                      std::shared_ptr<Parents> ...parents)
  -> std::shared_ptr<
    XformUpDownSignal<estd::decay_t<XForm>,
                      estd::decay_t<SetXForm>,
                      meta::pack<Parents...> >
    >
{
  using SignalT = XformUpDownSignal<estd::decay_t<XForm>,
                                    estd::decay_t<SetXForm>,
                                    meta::pack<Parents...> >;
  return linkToParents(
    std::make_shared<SignalT>(std::forward<XForm>(xform),
                            std::forward<SetXForm>(setXform),
                            std::move(parents)...));
}

} // namespace detail

} // namespace funken
} // namespace atria
