// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/interleave.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

#include <vector>

namespace atria {
namespace xform {

TEST(interleave, interleave)
{
  auto v1 = std::vector<int> {{ 1, 2, 3 }};
  auto v2 = std::vector<int> {{ 4, 5, 6 }};

  auto res = into_vector(interleave, v1, v2);
  EXPECT_EQ(res, (std::vector<int> { 1, 4, 2, 5, 3, 6 }));
}

TEST(interleave, interleave_termineates_early_enough)
{
  auto v1 = std::vector<int> {{ 1, 2, 3 }};
  auto v2 = std::vector<int> {{ 4, 5, 6 }};

  auto res = into_vector(comp(interleave, take(3)), v1, v2);
  EXPECT_EQ(res, (std::vector<int> { 1, 4, 2 }));
}

} // namespace xform
} // namespace atria
