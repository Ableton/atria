// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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
