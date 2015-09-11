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

#include <atria/meta/detected.hpp>

namespace atria {
namespace meta {

namespace detail {

template <typename T>
using value_type_t = typename T::value_type;

template <typename T>
using iterator_value_t = typename std::iterator_traits<T>::value_type;

template <typename T>
using dereference_t = estd::decay_t<decltype(*std::declval<T>())>;

template <typename T>
using getter_t = estd::decay_t<decltype(std::declval<T>().get())>;

} // namespace detail

/*!
 * Utility metafunction for accessing an underlying *value type*.
 * This metafunction tries, in this order:
 *
 *   - Nested type: `T::value_type`
 *   - Iterator traits: `std::iterator_traits<T>::value_type`
 *   - Decayed dereference: `std::decay_t<decltype(*std::declval<T>())>`
 *   - Decayed getter: `std::decay_t<decltype(std::declval<T>().get())>`
 *
 * The concrete semantics of this underlying value type might
 * be context dependent.  It can be partially spetialized for
 * different types.
 */
template <typename T>
struct get_value_type
  : detected_any<T,
                 detail::value_type_t,
                 detail::iterator_value_t,
                 detail::dereference_t,
                 detail::getter_t>
{};

/*!
 * Convenient alias for `get_value_type`
 */
template <typename T>
using value_t = eval_t<get_value_type<estd::decay_t<T> > >;

} // namespace meta
} // namespace atria
