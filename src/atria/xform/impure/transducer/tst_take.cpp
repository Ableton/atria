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
#include <atria/xform/impure/into.hpp>
#include <atria/xform/impure/transducer/take.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {
namespace impure {

TEST(take_impure, take)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = impure::into(std::vector<int> {}, impure::take(3), v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(take_impure, take_stops_early_enough2)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = impure::into(
    std::vector<int> {},
    comp(
      impure::take(3),
      map([](int x) {
          if (x > 4)
            throw std::runtime_error("bad!");
          return x;
        })),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

} // namespace impure
} // namespace xform
} // namespace atria
