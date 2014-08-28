// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/estd/ConceptsLite.hpp>
#include <ableton/estd/type_traits.hpp>
#include <utility>

namespace ableton {
namespace funken {

//!
// Concept for objects that provide values via a getter.
//
template <typename _>
struct In_value
  : estd::Concept<In_value<_> >
{
  template <typename T,
            typename V = estd::decay_t<estd::Value_type<T> > >
  auto requires(T&& x, V& v = std::declval<V&>()) -> decltype(
    estd::expressions(
      v = x.get(),
      v = ((const T&&) x).get()));
};

//!
// Concept for objects that provide values via a setter.
//
template <typename _>
struct Out_value
  : estd::Concept<Out_value<_> >
{
  template <typename T,
            typename V = estd::Value_type<T> >
  auto requires(T&& x, V& v = std::declval<V&>()) -> decltype(
    estd::expressions(
      (x.set(v), estd::canBeVoid),
      (x.set((const V&&) v), estd::canBeVoid)));
};

//!
// Concept for objects that meet boot `In_value` and `Out_value`.
// @see In_value
// @see Out_value
//
template <typename _>
struct Inout_value
  : estd::Concept<Inout_value<_> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    estd::expressions(
      estd::enable_if_t<(In_value<T>()), int>(),
      estd::enable_if_t<(Out_value<T>()), int>()));
};


//!
// Concept for values that can be commited.
//
template <typename _>
struct Root_value
  : estd::Concept<Root_value<_> >
{
  template <typename T>
  auto requires(T&& x) -> decltype(
    estd::expressions(
      (commit(x), estd::canBeVoid)));
};

} // namespace funken
} // namespace ableton
