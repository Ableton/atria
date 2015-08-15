// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(map, concept)
{
  meta::check<Transducer_spec(decltype(map(std::plus<int>{})),
                              meta::pack<int, int>,
                              int)>();
}

TEST(map, mapping)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  EXPECT_EQ(transduce(map(times2), std::plus<int>{}, 1, v), 25);
}

namespace {
int free_times2(int x) { return x * 2; }
} // anonymous namespace

TEST(map, mapping_invoke)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(transduce(map(free_times2), std::plus<int>{}, 1, v), 25);
}

} // namespace xform
} // namespace atria
