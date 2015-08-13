// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/remove.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(remove, concept)
{
  meta::check<Transducer_spec(decltype(filter(std::less<int>{})),
                              meta::pack<int, int>)>();
}

TEST(remove, simple)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  auto odd = [] (int x) { return x % 2 == 0; };

  auto res = transduce(
    comp(remove(odd), map(times2)), std::plus<int>{}, 1, v);
  EXPECT_EQ(res, 17);
}

} // namespace xform
} // namespace atria
