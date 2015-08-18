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
#include <atria/xform/into.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

#include <vector>

namespace atria {
namespace xform {

TEST(take, concept)
{
  meta::check<Transparent_transducer_spec(decltype(take(42)))>();
}

TEST(take, take)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<int> {}, take(3), v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(take, take_cat_terminates_early)
{
  auto v = std::vector<std::vector<int>> { { 1, 2 }, { 3 }, { 4, 5, 6 } };

  auto res = into(
    std::vector<int> {},
    comp(cat, map([] (int x) {
          EXPECT_LT(x, 5);
          return x;
        }), take(4)),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3, 4 }));
}

TEST(take, take_stops_early_enough)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(
    std::vector<int> {},
    comp(
      map([](int x) {
          if (x > 4)
            throw std::runtime_error("bad!");
          return x;
        }),
      take(3)),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(take, take_stops_early_enough2)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(
    std::vector<int> {},
    comp(
      take(3),
      map([](int x) {
          if (x > 4)
            throw std::runtime_error("bad!");
          return x;
        })),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(take, take_moves_the_state_through)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto spy = reduce(take(5)(first_rf), testing::copy_spy<>{}, v);
  EXPECT_EQ(spy.copied.count(), 0);
}

TEST(take, take_reduce_nested_finished)
{
  auto v = std::vector<std::vector<int>> { {1}, {2}, {3} };

  auto res = into(std::vector<int> {},
                  comp(cat, take(1)), v);
  EXPECT_EQ(res, (std::vector<int> {1}));
}

TEST(take, take_zero_not_supported)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  EXPECT_THROW(into(std::vector<int> {}, take(0), v),
               detail::empty_transducer_error);
}

} // namespace xform
} // namespace atria
