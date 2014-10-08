// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

//! @file
//
// Utility classes for definining and using concepts lite in C++11.
//
// C++14 introduces the notion of Concepts Lite.  Concepts, as in
// Concepts Lite, are just a `constexpr` nullary function templated
// over `T`, that returns a `bool` indicating whether `T` satisfies
// the concept.
//
// In this sense, `require` as defined in the new standard is a
// glorified `enable_if`.  Also, these concepts can already be defined
// in C++11.  The problem is, in C++11, constexpr functions are so
// limited that some of these functions are hard to define.  This
// namespace provides some utilities that make concepts easier to
// define and use.
//
// Here are some references where most of these techniques where
// borrowed from:
//
// - The C++ language 4th edition. (Stroustoup)
// - Concepts lite:
//   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3580.pdf
// - The origin library:
//   https://code.google.com/p/origin/
// - Concept checking in C++11
//   http://ericniebler.com/2013/11/23/concept-checking-in-c11/
//

#pragma once

#include <ableton/estd/type_traits.hpp>
#include <ableton/meta/Utils.hpp>
#include <ableton/meta/Pack.hpp>
#include <algorithm>

namespace ableton {
namespace meta {

//!
// Returns true if all the passed in values are true.
//
constexpr bool All()
{
  return true;
}

template <typename T, typename ...Ts>
constexpr bool All(T x, Ts ...xs)
{
  return x && All(xs...);
}

//!
// Concept that is always satisfied by the type or family of types
// that is passed to it.  Useful to simply check expressions about a
// type, using `decltype` expresions on a `Valid<>()`.
//
template <typename ...Ts>
constexpr bool Valid()
{
  return true;
}

//!
// Utility to define concepts in terms of other concepts or other
// kinds boolean requirements. For example:
//
// @code{.cpp}
// template <typename Arg>
// struct Inout_value
//   : meta::Concept<Inout_value<Arg> >
// {
//   template <typename T>
//   auto requires(T&& x) -> decltype(
//     meta::expressions(
//       meta::Require<(In_value<T>())>(),
//       meta::Require<(Out_value<T>())>()));
// };
// @endcode
//
template <bool Requirement, typename Result=int>
using Require = estd::enable_if_t<Requirement, Result>;

//!
// Allows to validate a sequence of expressions in a single decltype.
// Useful in combination with Valid. Not defined, use only in
// non-evaluated contexts.
//
template <typename ...Ts>
void expressions(Ts&&...);

namespace detail {

template <typename ConceptSig, typename Enable=void>
struct Satisfies : std::false_type {};

template <typename ConceptSpecT, typename ...Ts>
struct Satisfies<
    ConceptSpecT(Ts...),
    EnableIfType_t<
        decltype(std::declval<ConceptSpecT>().requires(std::declval<Ts>()...))
      >
    >
  : std::true_type
{};

} // namespace detail

//!
// Returns whether a concept signature `ConceptSig` is satisfied.  A
// concept signature has the form `ConceptSpec(T0, T1, ...)` where
// `ConceptSpec` is a concept specification type, and the types
// `T0`... are the types that we want to test against `ConceptSpec`.
//
// A *concept specification type* is a type that contains a template
// constexpr method `requires(T0&&, T1&&...)` that is available iff
// types `T0, T1...` satisfy the concept.  This method is never going
// to be used in an evaluated context, and its return type is
// irrelevant.  This enables usign a `decltype(...)` expression that
// validates the concept in the return type specification. For
// example:
//
// @code{.cpp}
// struct Equality_comparable_spec
// {
//    template <typename T>
//    auto require(T&& x) -> decltype(
//      expressions(
//        bool(x != x),
//        bool(x == x)));
//
//    template <typename T, typename U>
//    auto require(T&& x, U&& y) -> decltype(
//      expressions(
//        bool(x != y),
//        bool(x == y)));
// };
//
template<typename ConceptSig>
constexpr bool satisfies()
{
  return detail::Satisfies<ConceptSig>();
}

//!
// Like @a satisfies, but fails at compile-time when the specification
// is not met.  This is useful when debugging concept mismatches, as
// it will normally fail at the line of the specification that is not
// met.  However, it is not usable in SFINAE contexes.
//
template<typename ConceptSig>
constexpr bool check()
{
  return check(Pack<ConceptSig>{});
}

template<typename ConceptSpecT, typename ...Ts>
constexpr bool check(Pack<ConceptSpecT(Ts...)>)
{
  return Valid<decltype(
    std::declval<ConceptSpecT>().requires(
      std::declval<Ts>()...))>();
}

template<template<typename...>class ConceptSpecT, typename ...Ts>
constexpr bool check(Pack<ConceptSpecT<Ts...> >)
{
  return Valid<decltype(
    std::declval<ConceptSpecT<Ts...> >().requires(
      std::declval<Ts>()...))>();
}

//!
// Type that, given a `templated concept specification`, returns objects
// that convert to a boolean indicating whether the concept
// specifcation is satisfied by its template parameters.
//
// The concept signature can be an incomplete type at declaration time,
// allowing for it to be used as base class of concept specification
// types, turning them into entities syntactically equivalent to C++14
// constraints.  For example:
//
// @code{.cpp}
// template <typename T, typename U=T>
// struct Equality_comparable : Concept<Equality_comparable<T, U>>
// {
//    template <typename T, typename U>
//    auto require(T&& x, U&& y) -> decltype(
//      expressions(
//        bool(x != y),
//        bool(x == y)));
// };
// @endcode
//
// Note that it can also take a `ConceptSig` similar to the one in
// `satisfies`, allowing to declare the concept in two steps, as in:
//
// @code{.cpp}
// struct Equality_comparable_spec
// {
//    template <typename T, typename U>
//    auto require(T&& x, U&& y) -> decltype(
//      expressions(
//        bool(x != y),
//        bool(x == y)));
// };
//
// template <typename T, typename U=T>
// using Equality_comparable = Concept<Equality_comparable_spec(T, U)>;
// @endcode
//
// @see satisfies
//
template <typename ConceptSpecT>
struct Concept;

template <template<typename...> class ConceptSpecTplT, typename ...Ts>
struct Concept<ConceptSpecTplT<Ts...>>
{
  constexpr operator bool() const {
    return satisfies<ConceptSpecTplT<Ts...>(Ts...)>();
  }
};

template <typename ConceptSpecT, typename ...Ts>
struct Concept<ConceptSpecT(Ts...)>
{
  constexpr operator bool() const {
    return satisfies<ConceptSpecT(Ts...)>();
  }
};

//!
// Macro to check, at compile-time, that a concept is satisfied.  It
// generates a static assertion that checks the given concept for the
// given set of types.
//
#define ABL_ASSERT_CONCEPT(concept, types...)  \
  static_assert(                               \
    concept<types>(),                          \
    "Concept: " #concept                       \
    " must be satisfied by types: " #types)    \
  /**/

//!
// Macro to check that a concept is not satisfied by some
// types. Opposite of @a ABL_ASSERT_CONCEPT
//
#define ABL_ASSERT_NOT_CONCEPT(concept, types...)  \
  static_assert(                                   \
    !concept<types>(),                             \
    "Concept: " #concept                           \
    " must not be satisfied by types: " #types)    \
  /**/

} // namespace meta
} // namespace ableton
