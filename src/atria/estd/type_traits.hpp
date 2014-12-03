// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/Utils.hpp>
#include <type_traits>

namespace atria {
namespace estd {

//!
// Similar to C++14 std::decay_t
//
template <typename T>
using decay_t = typename std::decay<T>::type;

//!
// Similar to C++14 std::result_of_t
//
template <typename T>
using result_of_t = typename std::result_of<T>::type;

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

namespace detail {

template <typename T, typename Enable=void>
struct has_value_type : std::false_type {};
template <typename T>
struct has_value_type<T, meta::EnableIfType_t<typename T::value_type> >
  : std::true_type {};

template <typename T, typename Enable=void>
struct has_dereference : std::false_type {};
template <typename T>
struct has_dereference<T, meta::EnableIfType_t<decltype(*std::declval<T>())> >
  : std::true_type {};

template <typename T, typename Enable=void>
struct get_value_type {};
template <typename T>
struct get_value_type<T, estd::enable_if_t<has_value_type<T>::value> >
{
  using type = typename T::value_type;
};
template <typename T>
struct get_value_type<T, estd::enable_if_t<!has_value_type<T>::value &&
                                           has_dereference<T>::value> >
{
  using type = estd::decay_t<decltype(*std::declval<T>())>;
};

} // namespace detail

//!
// Very stupid implementation of C++14 Value_type, for a better one
// see the Origin library: https://code.google.com/p/origin/
//
template <typename T>
using Value_type = typename
  detail::get_value_type<estd::decay_t<T> >::type;

} // namespace estd
} // namespace atria
