// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

namespace atria {
namespace meta {

//!
// Binary metafunction that always returns the second type.  Useful to
// plug a dependent type expression in the second argument for SFINAE
//
template <typename CheckedType, typename Result = void>
struct EnableIfType
{
  using type = Result;
};

template<typename CheckedType, typename Result = void>
using EnableIfType_t = typename EnableIfType<CheckedType, Result>::type;

//!
// Type to enable making a type convertible from `void`.  The problem
// is that `void` can not be used as a parameter, so it is imposible
// to define a convertion between `void` and some types, in the
// degenerate cases where it is desirable.
//
// @see CouldNotFindCommonType
//
constexpr struct FromVoid {} fromVoid {};

//!
// Does nothing.
//
constexpr struct Noop
{
  template <typename ...Args>
  void operator() (Args&&...) const {}
} noop {};

//!
// Use to allow a `void` expression by chaining it in a comma operator
// thing.  A use-case is when expanding calls to variadic arguments
// that might be void, as in:
//
// @code{.cpp}
// template <typename ...Args>
// void doFoo(Args& args)
// {
//   using namespace meta;
//   noop((args.foo(), canBeVoid)...);
// }
// @endcode
//
// Another example is when writing concepts checking expressions that
// can be void, as in:
//
// @code{.cpp}
// template <typename Arg1, typename Arg2=Arg1>
// struct Swapable : Concept<Swapable<Arg1, Arg2>>
// {
//   template <typename T, typename U>
//   auto requires(T&& x, T&& y) -> decltype(
//     expressions(
//       (swap(x, y), canBeVoid),
//       (swap(y, x), canBeVoid)));
// };
// @endcode
//
constexpr int canBeVoid = 42;

} // namespace meta
} // namespace atria
