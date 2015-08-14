// Copyright (c) 2014, 2015 Ableton AG, Berlin
/*!
 * @file
 */

#pragma once

#include <functional>

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

} // namespace estd
} // namespace atria
