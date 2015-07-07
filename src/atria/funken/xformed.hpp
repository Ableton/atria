// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/in.hpp>
#include <atria/funken/inout.hpp>
#include <atria/funken/detail/xform_signals.hpp>
#include <atria/xform/transducer/map.hpp>

namespace atria {
namespace funken {

namespace detail {

template <typename SignalT>
struct xformed_input : private input_impl<SignalT>
{
  friend class access;
  using impl_t = input_impl<SignalT>;
  using typename impl_t::value_type;
  using impl_t::impl_t;
  using impl_t::get;
};

template <typename SignalT>
struct xformed_inoutput : private inoutput_impl<SignalT>
{
  friend class access;
  using impl_t = inoutput_impl<SignalT>;
  using typename impl_t::value_type;
  using impl_t::impl_t;
  using impl_t::get;
  using impl_t::set;
};

} // namespace detail

//!
// Returns a new in formed by applying a transducer `xform`
// on the successive values of the in.  If two `xform` parameters
// are given and the ins are also outs, values can be set back
// using the second `xform` to go back into the original domain.
//
template <typename Xform, typename ...InTs>
auto xformed(Xform&& xform, InTs&& ...ins)
  -> estd::enable_if_t<
    meta::all(In_value<InTs>()...),
    detail::xformed_input<
      typename decltype(
        detail::make_xform_down_signal(
          xform, detail::access::signal(ins)...)
        )::element_type
      >
    >
{
  return detail::make_xform_down_signal(
    std::forward<Xform>(xform),
    detail::access::signal(std::forward<InTs>(ins))...);
}

template <typename Xform, typename Xform2, typename ...InoutTs>
auto xformed(Xform&& xform, Xform2&& xform2, InoutTs&& ...ins)
  -> estd::enable_if_t<
  (!In_value<Xform2>() && meta::all(Inout_value<InoutTs>()...)),
  detail::xformed_inoutput<
    typename decltype(
      detail::make_xform_up_down_signal(
        xform, xform2, detail::access::signal(ins)...)
      )::element_type
    >
  >
{
  return detail::make_xform_up_down_signal(
    std::forward<Xform>(xform),
    std::forward<Xform2>(xform2),
    detail::access::signal(std::forward<InoutTs>(ins))...);
}

//!
// Import the update function.
// @see detail::update
//
using detail::update;

namespace detail {

struct at_rf_gen
{
  template <typename ReducingFnT, typename KeyT>
  struct apply
  {
    ReducingFnT step;
    KeyT key;

    //! @todo make variadic version
    template <typename StateT, typename InT>
    auto operator()(StateT&& s, InT&& i)
    -> decltype(true
                ? step(std::forward<StateT>(s), i.at(key))
                : std::forward<StateT>(s))
    {
      try
      {
        return step(std::forward<StateT>(s), i.at(key));
      }
      catch (const std::out_of_range&)
      {
        return s;
      }
    }
  };
};

template <typename KeyT>
struct at_updater
{
  KeyT key;

  template <typename CollectionT, typename ValueT>
  CollectionT operator() (CollectionT col, ValueT&& v) const
  {
    try
    {
      col.at(key) = std::forward<ValueT>(v);
    }
    catch (const std::out_of_range&) {}
    return col;
  }
};

} // namespace detail

//!
// Transducer that projects the key `key` from containers with a
// standard-style `at()` method.  It filters out ins without the
// given key.
//
template <typename KeyT>
auto xat(KeyT&& key)
  -> xform::transducer_impl<detail::at_rf_gen, estd::decay_t<KeyT> >
{
  return std::forward<KeyT>(key);
}

//!
// Update function that updates the `key` in a container with a
// standard-style `at()` method.  Does not update the container if the
// key was not already present.
// @see update
//
template <typename KeyT>
auto uat(KeyT&& key)
  -> detail::at_updater<estd::decay_t<KeyT> >
{
  return { std::forward<KeyT>(key) };
}

//!
// Returns *xformed* version of the ins using `xat`. If the ins
// are also outs, it is updated with `uat`.
// @see xat
// @see uat
//
template <typename KeyT, typename ...Ins>
auto atted(KeyT&& k, Ins&& ...ins)
  -> estd::enable_if_t<
    meta::all(In_value<Ins>() && !Out_value<Ins>()...),
    decltype(xformed(xat(k), ins...))
    >
{
  return xformed(xat(std::forward<KeyT>(k)),
                 std::forward<Ins>(ins)...);
}

template <typename KeyT, typename ...Ins>
auto atted(KeyT&& k, Ins&& ...ins)
  -> estd::enable_if_t<
    meta::all(Inout_value<Ins>()...),
    decltype(xformed(xat(k), update(uat(k)), ins...))
    >
{
  return xformed(xat(k),
                 update(uat(k)),
                 std::forward<Ins>(ins)...);
}

namespace detail {

template <typename AttrPtr>
struct get_attr_fn
{
  AttrPtr attr;

  //! @todo variadic version
  template <typename T>
  auto operator()(T&& x) const
    -> ABL_DECLTYPE_RETURN(x.*attr)
};

template <typename AttrPtr>
struct set_attr_fn
{
  AttrPtr attr;
  template <typename T, typename U>
  auto operator()(T x, U&& v) const -> T
  {
    x.*attr = std::forward<U>(v);
    modified(x);
    return x;
  }
};

} // namespace detail

//!
// Returns a unary function that dereferences the given pointer to
// member to the applied objects.
//
template <typename AttrPtrT>
auto get_attr(AttrPtrT p) -> detail::get_attr_fn<AttrPtrT> { return { p }; }

//!
// Returns a update function that uses the given pointer to member.
// @see update
//
template <typename AttrPtrT>
auto set_attr(AttrPtrT p) -> detail::set_attr_fn<AttrPtrT>{ return { p }; }

//!
// Given a pointer to member, returns a *xformed* version of the ins
// accessed through the member.  If the ins are also outs, the xformed
// version is an inout.
//
template <typename AttrPtrT, typename ...Ins>
auto attred(AttrPtrT attr, Ins&& ...ins)
  -> estd::enable_if_t<
    meta::all(In_value<Ins>() && !Out_value<Ins>()...),
          decltype(xformed(xform::map(get_attr(attr)), ins...))
    >
{
  return xformed(xform::map(get_attr(attr)),
                 std::forward<Ins>(ins)...);
}

template <typename AttrPtrT, typename ...Ins>
auto attred(AttrPtrT attr, Ins&& ...ins)
  -> estd::enable_if_t<
    meta::all(Inout_value<Ins>()...),
          decltype(xformed(xform::map(get_attr(attr)),
                           update(set_attr(attr)), ins...))
    >
{
  return xformed(xform::map(get_attr(attr)),
                 update(set_attr(attr)),
                 std::forward<Ins>(ins)...);
}

} // namespace funken
} // namespace atria
