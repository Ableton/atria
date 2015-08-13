// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(enumerate, enumerate)
{
  using tup = std::tuple<std::size_t, int>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(enumerate, v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup(0u, 13),
        tup(1u, 42),
        tup(2u, 5)
  }}));
}

TEST(enumerate, enumerate_from)
{
  using tup = std::tuple<char, int>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(enumerate_from('a'), v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup('a', 13),
        tup('b', 42),
        tup('c', 5)
  }}));
}

TEST(enumerate, generator)
{
  auto res = into_vector(comp(enumerate_from('a'), take(3)));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'b', 'c' }}));
}

} // namespace xform
} // namespace atria
