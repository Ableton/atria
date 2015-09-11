//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

namespace atria {
namespace meta {

/*!
 * Identity metafunction.
 */
template <typename T>
struct identity
{
  using type = T;
};

/*!
 * This is a type that pretends to be convertible to anything.  This
 * can be used as a placeholder for any parameter type in `result_of`
 * metacalls.
 *
 * @note Conversion is not defined. Only use in non-evaluated contexes.
 */
struct bottom
{
  template <typename T> operator T();
};

/*!
 * Type to enable making a type convertible from `void`.  The problem
 * is that `void` can not be used as a parameter, so it is imposible
 * to define a convertion between `void` and some types, in the
 * degenerate cases where it is desirable.
 *
 * @see could_not_find_common_type
 */
struct from_void {};

/*!
 * Does nothing.
 */
constexpr struct noop_t
{
  template <typename ...Args>
  void operator() (Args&&...) const {}
} noop {};

/*!
 * Use to allow a `void` expression by chaining it in a comma operator
 * thing.  A use-case is when expanding calls to variadic arguments
 * that might be void, as in:
 *
 * @code{.cpp}
 * template <typename ...Args>
 * void do_foo(Args& args)
 * {
 *   using namespace meta;
 *   noop((args.foo(), can_be_void)...);
 * }
 * @endcode
 *
 * Another example is when writing concepts checking expressions that
 * can be void, as in:
 *
 * @code{.cpp}
 * template <typename Arg1, typename Arg2=Arg1>
 * struct swapable : concept<swapable<Arg1, Arg2>>
 * {
 *   template <typename T, typename U>
 *   auto requires_(T&& x, T&& y) -> decltype(
 *     expressions(
 *       (swap(x, y), can_be_void),
 *       (swap(y, x), can_be_void)));
 * };
 * @endcode
 */
constexpr int can_be_void = 42;

/*!
 * Utility for defining generic functions with a deduced return type,
 * that are composed of a single expression.
 */
#define ABL_DECLTYPE_RETURN(body_expr)  \
  decltype(body_expr) { return (body_expr); }


#if ABL_CXX14
/*!
 * Macro forward universal-reference arguments.  This is only defined
 * in C++14, since outside of generic lambdas the macro-less syntax
 * should be preferred.
 */
#define ABL_FORWARD(x) std::forward<decltype(x)>(x)
#endif // ABL_CXX14

} // namespace meta
} // namespace atria
