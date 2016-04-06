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

#include <functional>
#include <atria/meta/utils.hpp>

namespace atria {
namespace estd {

#define ABL_DEFINE_CPP14_OPERATOR_1(name, op)                           \
  template <typename T = void>                                          \
  struct name  {                                                        \
    using argument_type = T;                                            \
    using result_type = T;                                              \
    T operator() (const T& a)                                           \
    {                                                                   \
      return op a;                                                      \
    }                                                                   \
  };                                                                    \
                                                                        \
  template <>                                                           \
  struct name<void>                                                     \
  {                                                                     \
    template <typename T, typename U>                                   \
    auto operator() (const T& a) const                                  \
      -> decltype(op a)                                                 \
    {                                                                   \
      return op a;                                                      \
    }                                                                   \
  };                                                                    \
  /**/

#define ABL_DEFINE_CPP14_OPERATOR_2(name, op)                           \
  template <typename T = void>                                          \
  struct name : std::name<T> {};                                        \
  template <>                                                           \
  struct name<void>                                                     \
  {                                                                     \
    template <typename T, typename U>                                   \
    auto operator() (const T& a, const U& b) const                      \
      -> decltype(a op b)                                               \
    {                                                                   \
      return a op b;                                                    \
    }                                                                   \
  };                                                                    \
  /**/

// Arithmetic
ABL_DEFINE_CPP14_OPERATOR_2(plus, +)
ABL_DEFINE_CPP14_OPERATOR_2(minus, -)
ABL_DEFINE_CPP14_OPERATOR_2(multiplies, *)
ABL_DEFINE_CPP14_OPERATOR_2(divides, /)
ABL_DEFINE_CPP14_OPERATOR_2(modulus, %)
ABL_DEFINE_CPP14_OPERATOR_1(negate, -)

// Comparison
ABL_DEFINE_CPP14_OPERATOR_2(equal_to, ==)
ABL_DEFINE_CPP14_OPERATOR_2(not_equal_to, !=)
ABL_DEFINE_CPP14_OPERATOR_2(greater, >)
ABL_DEFINE_CPP14_OPERATOR_2(less, <)
ABL_DEFINE_CPP14_OPERATOR_2(greater_equal, >=)
ABL_DEFINE_CPP14_OPERATOR_2(less_equal, <=)

// Logical
ABL_DEFINE_CPP14_OPERATOR_2(logical_and, &&)
ABL_DEFINE_CPP14_OPERATOR_2(logical_or, ||)
ABL_DEFINE_CPP14_OPERATOR_1(logical_not, !)

// Bitwise
ABL_DEFINE_CPP14_OPERATOR_2(bit_and, &)
ABL_DEFINE_CPP14_OPERATOR_2(bit_or, |)
ABL_DEFINE_CPP14_OPERATOR_2(bit_xor, ^)
ABL_DEFINE_CPP14_OPERATOR_1(bit_not, ~)

namespace detail {

#define ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(body_expr)  \
  decltype(body_expr) { return (body_expr); }

template <class F, class... Args>
inline auto INVOKE(F&& f, Args&&... args)
  -> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
    std::forward<F>(f)(std::forward<Args>(args)...))

template <class Base, class T, class Derived>
inline auto INVOKE(T Base::*pmd, Derived&& ref)
  -> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
    std::forward<Derived>(ref).*pmd)

template <class PMD, class Pointer>
inline auto INVOKE(PMD pmd, Pointer&& ptr)
  -> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
    (*std::forward<Pointer>(ptr)).*pmd)

template <class Base, class T, class Derived, class... Args>
inline auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
-> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
  (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))

template <class PMF, class Pointer, class... Args>
inline auto INVOKE(PMF pmf, Pointer&& ptr, Args&&... args)
  -> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
    ((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...))

} // namespace detail

/*!
 * Like C++17 `std::invoke`
 */
template <class F, class... ArgTypes>
auto invoke(F&& f, ArgTypes&&... args)
  -> ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN(
    detail::INVOKE(std::forward<F>(f), std::forward<ArgTypes>(args)...))

#undef ABL_ESTD_FUNCTIONAL_DECLTYPE_RETURN

} // namespace estd
} // namespace atria
