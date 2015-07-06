// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/reduce.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(reduce, protect_against_moved_self_assignment)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(reduce(first_rf, v, v), v);
}

} // namespace xform
} // namespace atria
