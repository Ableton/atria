// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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
