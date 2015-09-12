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

#include <atria/meta/utils.hpp>
#include <type_traits>

namespace atria {
namespace estd {

namespace detail {

template<typename... Ts>
struct make_void
{
  using type = void;
};

} // namespace detail

/*!
 * Similar to C++17 std::void_t
 */
template<typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

/*!
 * Similar to C++14 std::decay_t
 */
template <typename T>
using decay_t = typename std::decay<T>::type;

/*!
 * Similar to C++14 std::result_of_t
 */
template <typename T>
using result_of_t = typename std::result_of<T>::type;

/*!
 * Similar to C++14 std::conditional_t
 */
template <bool X, typename T, typename F>
using conditional_t = typename std::conditional<X, T, F>::type;

/*!
 * Similar to C++14 std::remove_reference_t
 */
template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

/*!
 * Similar to C++14 std::remove_const_t
 */
template <typename T>
using remove_const_t = typename std::remove_const<T>::type;

/*!
 * Similar to C++14 std::enable_if_t
 */
template <bool X, typename T=void>
using enable_if_t = typename std::enable_if<X, T>::type;

namespace detail {

template <typename T, typename Enable=void>
struct has_value_type : std::false_type {};
template <typename T>
struct has_value_type<T, void_t<typename T::value_type> >
  : std::true_type {};

template <typename T, typename Enable=void>
struct has_dereference : std::false_type {};
template <typename T>
struct has_dereference<T, void_t<decltype(*std::declval<T>())> >
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

/*!
 * Very stupid implementation of C++14 Value_type, for a better one
 * see the Origin library: https://code.google.com/p/origin/
 */
template <typename T>
using Value_type = typename
  detail::get_value_type<estd::decay_t<T> >::type;

} // namespace estd
} // namespace atria
