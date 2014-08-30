// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/In.hpp>
#include <ableton/funken/Inout.hpp>
#include <ableton/funken/detail/XformSignals.hpp>

namespace ableton {
namespace funken {

namespace detail {

template <typename SignalT>
struct XformedIn : private InImpl<SignalT>
{
  friend class Access;
  using ImplT = InImpl<SignalT>;
  using typename ImplT::value_type;
  using ImplT::ImplT;
  using ImplT::get;
};

template <typename SignalT>
struct XformedInout : private InoutImpl<SignalT>
{
  friend class Access;
  using ImplT = InoutImpl<SignalT>;
  using typename ImplT::value_type;
  using ImplT::ImplT;
  using ImplT::get;
  using ImplT::set;
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
    estd::All(In_value<InTs>()...),
    detail::XformedIn<
      typename decltype(
        detail::makeXformDownSignal(
          xform, detail::Access::signal(ins)...)
        )::element_type
      >
    >
{
  return detail::makeXformDownSignal(
    std::forward<Xform>(xform),
    detail::Access::signal(std::forward<InTs>(ins))...);
}

template <typename Xform, typename Xform2, typename ...InoutTs>
auto xformed(Xform&& xform, Xform2&& xform2, InoutTs&& ...ins)
  -> estd::enable_if_t<
  (!In_value<Xform2>() && estd::All(Inout_value<InoutTs>()...)),
  detail::XformedInout<
    typename decltype(
      detail::makeXformUpDownSignal(
        xform, xform2, detail::Access::signal(ins)...)
      )::element_type
    >
  >
{
  return detail::makeXformUpDownSignal(
    std::forward<Xform>(xform),
    std::forward<Xform2>(xform2),
    detail::Access::signal(std::forward<InoutTs>(ins))...);
}

//!
// Import the update function.
// @see detail::update
//
using detail::update;

namespace detail {

struct AtReducer
{
  template <typename ReducerT, typename KeyT>
  struct Reducer
  {
    ReducerT reducer;
    KeyT key;

    //! @todo make variadic version
    template <typename StateT, typename InT>
    auto operator()(StateT&& s, InT&& i)
    -> decltype(true
                ? reducer(std::forward<StateT>(s), i.at(key))
                : std::forward<StateT>(s))
    {
      try
      {
        return reducer(std::forward<StateT>(s), i.at(key));
      }
      catch (const std::out_of_range&)
      {
        return s;
      }
    }
  };
};

template <typename KeyT>
struct AtUpdater
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
  -> detail::Transducer<detail::AtReducer, estd::decay_t<KeyT> >
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
  -> detail::AtUpdater<estd::decay_t<KeyT> >
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
    estd::All(In_value<Ins>() && !Out_value<Ins>()...),
    decltype(xformed(xat(k), ins...))
    >
{
  return xformed(xat(std::forward<KeyT>(k)),
                 std::forward<Ins>(ins)...);
}

template <typename KeyT, typename ...Ins>
auto atted(KeyT&& k, Ins&& ...ins)
  -> estd::enable_if_t<
    estd::All(Inout_value<Ins>()...),
    decltype(xformed(xat(k), update(uat(k)), ins...))
    >
{
  return xformed(xat(k),
                 update(uat(k)),
                 std::forward<Ins>(ins)...);
}

namespace detail {

template <typename AttrPtr>
struct GetAttr
{
  AttrPtr pAttr;

  //! @todo variadic version
  template <typename T>
  auto operator()(T&& x) const -> decltype(x.*pAttr)
  {
    return x.*pAttr;
  }
};

template <typename AttrPtr>
struct SetAttr
{
  AttrPtr pAttr;
  template <typename T, typename U>
  auto operator()(T x, U&& v) const -> T
  {
    x.*pAttr = v;
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
auto getAttr(AttrPtrT p) -> detail::GetAttr<AttrPtrT> { return { p }; }

//!
// Returns a update function that uses the given pointer to member.
// @see update
//
template <typename AttrPtrT>
auto setAttr(AttrPtrT p) -> detail::SetAttr<AttrPtrT>{ return { p }; }

//!
// Given a pointer to member, returns a *xformed* version of the ins
// accessed through the member.  If the ins are also outs, the xformed
// version is an inout.
//
template <typename AttrPtrT, typename ...Ins>
auto attred(AttrPtrT pAttr, Ins&& ...ins)
  -> estd::enable_if_t<
    estd::All(In_value<Ins>() && !Out_value<Ins>()...),
    decltype(xformed(map(getAttr(pAttr)), ins...))
    >
{
  return xformed(map(getAttr(pAttr)),
                 std::forward<Ins>(ins)...);
}

template <typename AttrPtrT, typename ...Ins>
auto attred(AttrPtrT pAttr, Ins&& ...ins)
  -> estd::enable_if_t<
    estd::All(Inout_value<Ins>()...),
    decltype(xformed(map(getAttr(pAttr)),
                     update(setAttr(pAttr)), ins...))
    >
{
  return xformed(map(getAttr(pAttr)),
                 update(setAttr(pAttr)),
                 std::forward<Ins>(ins)...);
}

} // namespace funken
} // namespace ableton
