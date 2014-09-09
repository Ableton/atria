// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/meta/Concept.hpp>
#include <ableton/estd/type_traits.hpp>
#include <utility>

namespace ableton {
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
      v = ((const T&&) x).get()));
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
      (x.set((const V&&) v), meta::canBeVoid)));
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
      estd::enable_if_t<(In_value<T>()), int>(),
      estd::enable_if_t<(Out_value<T>()), int>()));
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
} // namespace ableton
