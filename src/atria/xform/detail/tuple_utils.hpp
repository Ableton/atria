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

#include <atria/estd/type_traits.hpp>
#include <tuple>

namespace atria {
namespace xform {
namespace detail {

template <std::size_t Index, std::size_t Max>
struct tuple_all_neq_t
{
  template <typename Tuple1T, typename Tuple2T>
  bool operator()(Tuple1T&& t1, Tuple2T&& t2)
  {
    return
      std::get<Index>(std::forward<Tuple1T>(t1)) !=
      std::get<Index>(std::forward<Tuple2T>(t2)) &&
      tuple_all_neq_t<Index + 1, Max>{} (
        std::forward<Tuple1T>(t1),
        std::forward<Tuple2T>(t2));
  }
};

template <std::size_t Max>
struct tuple_all_neq_t<Max, Max>
{
  template <typename Tuple1T, typename Tuple2T>
  bool operator()(Tuple1T&&, Tuple2T&&)
  {
    return true;
  }
};

template <typename Tuple1T, typename Tuple2T>
bool tuple_all_neq(Tuple1T&& t1, Tuple2T&& t2)
{
  constexpr auto size1 = std::tuple_size<estd::decay_t<Tuple1T> >::value;
  constexpr auto size2 = std::tuple_size<estd::decay_t<Tuple2T> >::value;
  static_assert(size1 == size2, "");

  using impl_t = tuple_all_neq_t<0u, (size1 > size2 ? size2 : size1)>;

  return impl_t{} (
    std::forward<Tuple1T>(t1),
    std::forward<Tuple2T>(t2));
}

} // namespace detail
} // namespace xform
} // namespace atria
