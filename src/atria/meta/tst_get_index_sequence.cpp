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

#include <atria/meta/get_index_sequence.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace meta {

TEST(get_index_sequence, tuple)
{
  static_assert(std::is_same<get_index_sequence<std::tuple<> >,
                             estd::make_index_sequence<0> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::tuple<int> >,
                             estd::make_index_sequence<1> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::tuple<int, double> >,
                             estd::make_index_sequence<2> >{}, "");
}

TEST(get_index_sequence, pair)
{
  static_assert(std::is_same<get_index_sequence<std::pair<int, char> >,
                             estd::make_index_sequence<2> >{}, "");
}

TEST(get_index_sequence, array)
{
  static_assert(std::is_same<get_index_sequence<std::array<int, 0> >,
                             estd::make_index_sequence<0> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::array<int, 1> >,
                             estd::make_index_sequence<1> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::array<int, 10> >,
                             estd::make_index_sequence<10> >{}, "");
}

namespace {

struct custom {};

template <std::size_t N>
auto get(const custom& c)
  -> estd::enable_if_t<(N < 3), int>;

} // anonymous namespace

TEST(get_index_sequence, custom)
{
  static_assert(std::is_same<get_index_sequence<custom>,
                             estd::make_index_sequence<3> >{}, "");
}

namespace {

struct errorish {};

} // anonymous namesapce

TEST(get_index_sequence, error)
{
  static_assert(std::is_same<get_index_sequence<errorish>,
                             could_not_get_index_sequence>{}, "");
  static_assert(std::is_same<get_index_sequence<int>,
                             could_not_get_index_sequence>{}, "");
}

} // namespace meta
} // namespace atria
