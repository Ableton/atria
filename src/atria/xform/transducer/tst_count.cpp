// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/count.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(count, count)
{
  using tup = std::tuple<int, std::size_t>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(count(), v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup(13, 0u),
        tup(42, 1u),
        tup(5, 2u)
  }}));
}

TEST(count, generator)
{
  auto res = into_vector(comp(count('a'), take(3)));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'b', 'c' }}));
}

TEST(count, stepped)
{
  auto res = into_vector(comp(count(1.0, 0.5), take(3)));
  EXPECT_EQ(res, (std::vector<double> {{ 1.0, 1.5, 2.0 }}));
}

} // namespace xform
} // namespace atria
