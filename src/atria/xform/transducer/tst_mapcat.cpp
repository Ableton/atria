
// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/mapcat.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(mapcat, mapcat)
{
  auto v = std::vector<std::vector<int>> { { 1, 2 }, { 3 }, { 4, 5, 6 } };

  auto res = into(std::vector<int> {}, mapcat([](int x) { return x * 2; }), v);
  EXPECT_EQ(res, (std::vector<int> { 2, 4, 6, 8, 10, 12 }));
}

} // namespace xform
} // namespace atria
