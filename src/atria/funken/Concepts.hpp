// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/Concept.hpp>
#include <atria/estd/type_traits.hpp>
#include <utility>

namespace atria {
namespace funken {

//!
// Concept for objects that provide values via a getter.
//
template <typename Arg>
struct In_value
  : meta::Concept<In_value<Arg> >
{
  template <typename T,
            typename V = estd::decay_t<estd::Value_type<T> > >
  auto requires(T&& x, V& v = std::declval<V&>()) -> decltype(
    meta::expressions(
      v = x.get(),
      v = static_cast<const T&&>(x).get()));
};

//!
// Concept for objects that provide values via a setter.
//
template <typename Arg>
struct Out_value
  : meta::Concept<Out_value<Arg> >
{
  template <typename T,
            typename V = estd::Value_type<T> >
  auto requires(T&& x, V& v = std::declval<V&>()) -> decltype(
    meta::expressions(
      (x.set(v), meta::canBeVoid),
      (x.set(static_cast<const V&&>(v)), meta::canBeVoid)));
};

//!
// Concept for objects that meet boot `In_value` and `Out_value`.
// @see In_value
// @see Out_value
//
template <typename Arg>
struct Inout_value
  : meta::Concept<Inout_value<Arg> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    meta::expressions(
      meta::Require<(In_value<T>())>(),
      meta::Require<(Out_value<T>())>()));
};


//!
// Concept for values that can be commited.
//
template <typename Arg>
struct Root_value
  : meta::Concept<Root_value<Arg> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    meta::expressions(
      (commit(x), meta::canBeVoid)));
};

} // namespace funken
} // namespace atria
