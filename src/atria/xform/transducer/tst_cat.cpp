// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/testing/gtest.hpp>

#include <vector>
#include <list>

namespace atria {
namespace xform {

TEST(cat, concept)
{
  meta::check<Transducer_spec(cat_t, std::vector<int>, int)>();
  meta::check<Transducer_spec(cat_t, std::list<std::string>, std::string)>();
}

TEST(cat, cat)
{
  auto v = std::vector<std::vector<int>> { { 1, 2 }, { 3 }, { 4, 5, 6 } };

  auto res = into(std::vector<int> {}, cat, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3, 4, 5, 6 }));
}

} // namespace xform
} // namespace atria
