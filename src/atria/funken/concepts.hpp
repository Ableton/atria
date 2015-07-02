// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/concept.hpp>
#include <atria/estd/type_traits.hpp>
#include <utility>
#include <cassert>

namespace atria {
namespace funken {

template <typename T>
auto declval_() -> typename std::add_rvalue_reference<T>::type
{
  assert(!"You should never run this function!");
  return *static_cast<estd::decay_t<T>*>(nullptr);
}

//!
// Concept for objects that provide values via a getter.
//
template <typename Arg>
struct In_value
  : meta::concept<In_value<Arg> >
{
  template <typename T,
            typename V = estd::decay_t<estd::Value_type<T> > >
  auto requires(T&& x, V& v = declval_<V&>()) -> decltype(
    meta::expressions(
      v = x.get(),
      v = static_cast<const T&&>(x).get()));
};

//!
// Concept for objects that provide values via a setter.
//
template <typename Arg>
struct Out_value
  : meta::concept<Out_value<Arg> >
{
  template <typename T,
            typename V = estd::Value_type<T> >
  auto requires(T&& x, V& v = declval_<V&>()) -> decltype(
    meta::expressions(
      (x.set(v), meta::can_be_void),
      (x.set(static_cast<const V&&>(v)), meta::can_be_void)));
};

//!
// Concept for objects that meet boot `In_value` and `Out_value`.
// @see In_value
// @see Out_value
//
template <typename Arg>
struct Inout_value
  : meta::concept<Inout_value<Arg> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    meta::expressions(
      meta::require<(In_value<T>())>(),
      meta::require<(Out_value<T>())>()));
};


//!
// Concept for values that can be commited.
//
template <typename Arg>
struct Root_value
  : meta::concept<Root_value<Arg> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    meta::expressions(
      (commit(x), meta::can_be_void)));
};

} // namespace funken
} // namespace atria
