// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(into, take)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<int> {}, take(3), v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, take_cat_terminates_early)
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

TEST(into, take_stops_early_enough)
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

TEST(into, take_stops_early_enough2)
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

} // namespace xform
} // namespace atria
