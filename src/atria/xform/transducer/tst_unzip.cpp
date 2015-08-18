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

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/unzip.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/xform/reducing/first_rf.hpp>

#include <atria/testing/gtest.hpp>
#include <iostream>

namespace atria {
namespace xform {

TEST(unzip, unzip_transducer)
{
  using tup = std::tuple<int, double>;

  auto v1 = std::vector<tup> {{ tup(13, 1.1), tup(42, 2.2), tup(5, 3.3) }};

  auto res = transduce(
    unzip,
    [] (double x, int y, double z) {
      return x + y + z;
    },
    1.0,
    v1);

  EXPECT_DOUBLE_EQ(res, 67.6);
}

TEST(unzip, unzip_transducer_variadic_multitype)
{
  using tup1 = std::tuple<int, double>;
  using tup2 = std::tuple<char>;
  using arr  = std::array<int, 2>;

  auto v1 = std::vector<tup1> {{ tup1(13, 1.1), tup1(42, 2.2), tup1(5, 3.3) }};
  auto v2 = std::vector<short> {{ 1, 2, 3}};
  auto v3 = std::vector<tup2> {{ tup2('a'), tup2('b'), tup2('c') }};
  auto v4 = std::vector<arr> {{ arr{{1, 2}}, arr{{3, 4}}, arr{{5, 6}} }};

  auto res = transduce(
    unzip,
    [] (double x, int y, double z, short v, char w, int a, int b) {
      return x + y + z + v + w + a + b;
    },
    1.0,
    v1, v2, v3, v4);

  EXPECT_DOUBLE_EQ(res, 388.6);
}

} // namespace xform
} // namespace atria
