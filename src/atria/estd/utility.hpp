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

#include <utility>

namespace atria {
namespace estd {

template <typename T, T ...Ints>
struct integer_sequence
{
  using value_type = T;
  static constexpr std::size_t size()
  {
    return sizeof...(Ints);
  }
};

template<std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

namespace detail {

template <typename T, T Curr, T Limit, typename Accum>
struct make_integer_sequence;

template <typename T, T Limit, T ...Ns>
struct make_integer_sequence<T, Limit, Limit, integer_sequence<T, Ns...>>
{
  using type = integer_sequence<T, Ns...>;
};

template <typename T, T Curr, T Limit, T ...Ns>
struct make_integer_sequence<T, Curr, Limit, integer_sequence<T, Ns...>>
  : make_integer_sequence<
      T, (Curr + 1), Limit, integer_sequence<T, Ns..., Curr>
    >
{};

} // namespace detail

template<class T, T N>
using make_integer_sequence = typename detail::make_integer_sequence<
  T, 0, N, integer_sequence<T> >::type;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

} // namespace estd
} // namespace atria
