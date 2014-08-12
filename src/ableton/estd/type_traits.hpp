// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <type_traits>

namespace ableton {
namespace estd {

//!
// Very stupid implementation of C++14 Value_type, for a better one
// see the Origin library: https://code.google.com/p/origin/
//
template <typename T>
using Value_type = typename T::value_type;

//!
// Similar to C++14 std::decay_t
//
template <typename T>
using decay_t = typename std::decay<T>::type;

//!
// Similar to C++14 std::conditional_t
//
template <bool X, typename T, typename F>
using conditional_t = typename std::conditional<X, T, F>::type;

//!
// Similar to C++14 std::enable_if_t
//
template <bool X, typename T=void>
using enable_if_t = typename std::enable_if<X, T>::type;

} // namespace estd
} // namespace ableton
