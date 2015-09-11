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

template <class Default, class AlwaysVoid,
          template<class...> class Op, class... Args>
struct detector
{
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template<class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...> >, Op, Args...>
{
  using value_t = std::true_type;
  using type = Op<Args...>;
};

} // namespace detail

/*!
 * Similar to TS Fundamentals 2 `std::nonesuch`
 */
struct nonesuch
{
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
};

/*!
 * Similar to TS Fundamentals 2 `std::is_detected`
 */
template <template<class...> class Op, class... Args>
using is_detected =
  typename detail::detector<nonesuch, void, Op, Args...>::value_t;

/*!
 * Similar to TS Fundamentals 2 `std::detected_t`
 */
template <template<class...> class Op, class... Args>
using detected_t =
  typename detail::detector<nonesuch, void, Op, Args...>::type;

/*!
 * Similar to TS Fundamentals 2 `std::dected_or`
 */
template <class Default, template<class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

/*!
 * Similar to TS Fundamentals 2 `std::dected_or_t`
 */
template <class Default, template<class...> class Op, class... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

/*!
 * Similar to TS Fundamentals 2 `std::is_detected_exact`
 */
template <class Expected, template<class...> class Op, class... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...> >;

/*!
 * Similar to TS Fundamentals 2 `std::is_detected_exact_v`
 */
template <class To, template<class...> class Op, class... Args>
using is_detected_convertible =
  std::is_convertible<detected_t<Op, Args...>, To>;

#if ABL_CXX14

/*!
 * Similar to TS Fundamentals 2 `std::dected_or`
 */
template <template<class...> class Op, class... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

/*!
 * Similar to TS Fundamentals 2 `std::is_detected_exact_v`
 */
template <class Expected, template<class...> class Op, class... Args>
constexpr bool is_detected_exact_v =
  is_detected_exact<Expected, Op, Args...>::value;

/*!
 * Similar to TS Fundamentals 2 `std::is_detected_convertible_v`
 */
template <class To, template<class...> class Op, class... Args>
constexpr bool is_detected_convertible_v =
  is_detected_convertible<To, Op, Args...>::value;

#endif // ABL_CXX14

} // namespace estd
} // namespace atria
