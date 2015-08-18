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
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/range.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(range, stop)
{
  auto res = into_vector(range(3));
  EXPECT_EQ(res, (std::vector<std::size_t> {{ 0, 1, 2 }}));
}

TEST(range, start_stop)
{
  auto res = into_vector(range(2, 6));
  EXPECT_EQ(res, (std::vector<int> {{ 2, 3, 4, 5 }}));
}

TEST(range, start_stop_step)
{
  auto res = into_vector(range(2, 6, 2));
  EXPECT_EQ(res, (std::vector<int> {{ 2, 4 }}));
}

TEST(range, start_stop_step_floating_point)
{
  auto res = into_vector(range(2.0, 6.0, 1.2));
  auto expected = std::vector<double> {{ 2.0, 3.2, 4.4, 5.6 }};
  EXPECT_TRUE(transduce(map([](double x, double y) {
          EXPECT_DOUBLE_EQ(x, y);
          return true;
        }),
      last_rf, true, res, expected));
}

} // namespace xform
} // namespace atria
