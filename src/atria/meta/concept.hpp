// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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

#include <atria/estd/type_traits.hpp>
#include <atria/meta/utils.hpp>
#include <atria/meta/pack.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <algorithm>

namespace atria {
namespace meta {

//!
// Returns true if all the passed in values are true.
//
constexpr bool all()
{
  return true;
}

template <typename T, typename ...Ts>
constexpr bool all(T x, Ts ...xs)
{
  return x && all(xs...);
}

//!
// Concept that is always satisfied by the type or family of types
// that is passed to it.  Useful to simply check expressions about a
// type, using `decltype` expresions on a `Valid<>()`.
//
template <typename ...Ts>
constexpr bool valid()
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
//   : meta::concept<Inout_value<Arg> >
// {
//   template <typename T>
//   auto requires_(T&& x) -> decltype(
//     meta::expressions(
//       meta::require<(In_value<T>())>(),
//       meta::require<(Out_value<T>())>()));
// };
// @endcode
//
template <bool Requirement>
using require = estd::enable_if_t<Requirement, int>;

//!
// Allows to validate a sequence of expressions in a single decltype.
// Useful in combination with Valid. Not defined, use only in
// non-evaluated contexts.
//
template <typename ...Ts>
void expressions(Ts&&...);

//!
// Returns whether a concept signature `ConceptSig` is satisfied.  A
// concept signature has the form `ConceptSpec(T0, T1, ...)` where
// `ConceptSpec` is a concept specification type, and the types
// `T0`... are the types that we want to test against `ConceptSpec`.
//
// A *concept specification type* is a type that contains a template
// constexpr method `requires_(T0&&, T1&&...)` that is available iff
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
//    auto requires_(T&& x) -> decltype(
//      expressions(
//        bool(x != x),
//        bool(x == x)));
//
//    template <typename T, typename U>
//    auto requires_(T&& x, U&& y) -> decltype(
//      expressions(
//        bool(x != y),
//        bool(x == y)));
// };
//
template <typename ConceptSig, typename Enable=void>
struct models
  : std::false_type {};

template <typename ConceptSpecT, typename ...Ts>
struct models<
    ConceptSpecT(Ts...),
    estd::void_t<
        decltype(std::declval<ConceptSpecT>().requires_(
                   std::declval<Ts>()...))
      >
    >
  : std::true_type
{};

template <typename ConceptSpecT, typename T>
struct models_ : models<ConceptSpecT(T)> {};

//!
// Like @a models, but fails at compile-time when the specification
// is not met.  This is useful when debugging concept mismatches, as
// it will normally fail at the line of the specification that is not
// met.  However, it is not usable in SFINAE contexes.
//
template<typename ConceptSig>
constexpr bool check()
{
  return check(pack<ConceptSig>{});
}

template<typename ConceptSpecT, typename ...Ts>
constexpr bool check(pack<ConceptSpecT(Ts...)>)
{
  return valid<decltype(
    std::declval<ConceptSpecT>().requires_(
      std::declval<Ts>()...))>();
}

template<template<typename...>class ConceptSpecT, typename ...Ts>
constexpr bool check(pack<ConceptSpecT<Ts...> >)
{
  return valid<decltype(
    std::declval<ConceptSpecT<Ts...> >().requires_(
      std::declval<Ts>()...))>();
}

//!
// Macro for future-proof concept-lite like concepts.  In the
// future, it will expand to the `concept` keyword, for now it expands
// to `constexpr`. Example:
//
// @code{.cpp}
// struct My_concept_spec { ... };
//
// template <typename T>
// ABL_CONCEPT bool My_concept() {
//   return models<My_concept_spec(T)>();
// };
// @endcode
//
#define ABL_CONCEPT constexpr

//!
// Helper macro to define concept-lite style concepts.  The macro
// defines:
//
// - A concept-lite like *concept* named `{concept_name}`. In pre-C++17
//   compilers this is just a `constexpr` function template that
//   returns `bool`.
//
// - It opens the definition of a type `{concept_name}_spec` that is a
//   meant to be a *concept spectification*. @see models.
//
// Example:
//
// @code{.cpp}
// ABL_CONCEPT_SPEC(Equality_comparable)
// {
//    template <typename T, typename U>
//    auto requires_(T&& x, U&& y) -> decltype(
//      expressions(
//        bool(x != y),
//        bool(x == y)));
//
//    template <typename T>
//    auto requires_(T&& x) -> decltype(
//      requires_(x, x));
// };
// @endcode
//
#define ABL_CONCEPT_SPEC(concept_name)                                  \
  struct concept_name ## _spec;                                         \
  template <typename... Ts>                                             \
  ABL_CONCEPT bool concept_name()                                       \
  {                                                                     \
    return ::atria::meta::models<concept_name ## _spec (Ts...)>();      \
  }                                                                     \
  struct concept_name ## _spec
  /**/

//!
// Metafunction that given a type @a T and a one or more of MPL
// *metafunction classes* @a Mfs that boolean metafunctions, returns
// whether any of these metafunctios @a Mfs returns true when applied
// with @a T.
//
template <typename T, typename ...Mfs>
struct if_any;

template <typename T, typename Mf, typename ...Mfs>
struct if_any<T, Mf, Mfs...> : boost::mpl::eval_if<
    typename boost::mpl::apply1<Mf, T>::type,
    std::true_type,
    if_any<T, Mfs...>
  >
{
};

template <typename T, typename Mf>
struct if_any<T, Mf> {
  using type = typename boost::mpl::apply1<Mf, T>::type;
};

//!
// Like @a require, but based on the semantics of `if_any`.
//
template <typename T, typename... Mfs>
using require_any = estd::enable_if_t<
  if_any<T, Mfs...>::type::value,
  int>;


//!
// Macro to check, at compile-time, that a concept is satisfied.  It
// generates a static assertion that checks the given concept for the
// given set of types.
//
#define ABL_ASSERT_CONCEPT(concept, ...)             \
  static_assert(                                     \
    concept<__VA_ARGS__>(),                          \
    "Concept: " #concept                             \
    " must be satisfied by types: " #__VA_ARGS__)    \
  /**/

//!
// Macro to check that a concept is not satisfied by some
// types. Opposite of @a ABL_ASSERT_CONCEPT
//
#define ABL_ASSERT_NOT_CONCEPT(concept, ...)             \
  static_assert(                                         \
    !concept<__VA_ARGS__>(),                             \
    "Concept: " #concept                                 \
    " must not be satisfied by types: " #__VA_ARGS__)    \
  /**/

} // namespace meta
} // namespace atria
