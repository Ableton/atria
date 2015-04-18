// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

namespace atria {
namespace meta {

//!
// Binary metafunction that always returns the second type.  Useful to
// plug a dependent type expression in the second argument for SFINAE
//
template <typename CheckedType, typename Result = void>
struct enable_if_type
{
  using type = Result;
};

template<typename CheckedType, typename Result = void>
using enable_if_type_t = typename enable_if_type<CheckedType, Result>::type;

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
//   auto requires(T&& x, T&& y) -> decltype(
//     expressions(
//       (swap(x, y), can_be_void),
//       (swap(y, x), can_be_void)));
// };
// @endcode
//
constexpr int can_be_void = 42;

} // namespace meta
} // namespace atria
