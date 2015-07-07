// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

namespace atria {
namespace meta {

//!
// Type to enable making a type convertible from `void`.  The problem
// is that `void` can not be used as a parameter, so it is imposible
// to define a convertion between `void` and some types, in the
// degenerate cases where it is desirable.
//
// @see could_not_find_common_type
//
struct from_void {};

//!
// Does nothing.
//
constexpr struct noop_t
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
// void do_foo(Args& args)
// {
//   using namespace meta;
//   noop((args.foo(), can_be_void)...);
// }
// @endcode
//
// Another example is when writing concepts checking expressions that
// can be void, as in:
//
// @code{.cpp}
// template <typename Arg1, typename Arg2=Arg1>
// struct swapable : concept<swapable<Arg1, Arg2>>
// {
//   template <typename T, typename U>
//   auto requires_(T&& x, T&& y) -> decltype(
//     expressions(
//       (swap(x, y), can_be_void),
//       (swap(y, x), can_be_void)));
// };
// @endcode
//
constexpr int can_be_void = 42;

/*!
 * Utility for defining generic functions with a deduced return type,
 * that are composed of a single expression.
 */
#define ABL_DECLTYPE_RETURN(body_expr)  \
  decltype(body_expr) { return (body_expr); }

} // namespace meta
} // namespace atria
