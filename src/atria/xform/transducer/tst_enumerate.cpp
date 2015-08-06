// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/enumerate.hpp>

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

namespace impure {


TEST(enumerate_impure, enumerate)
{
  using tup = std::tuple<std::size_t, int>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(impure::enumerate, v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup(0u, 13),
        tup(1u, 42),
        tup(2u, 5)
  }}));
}

TEST(enumerate_impure, enumerate_from)
{
  using tup = std::tuple<char, int>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(impure::enumerate_from('a'), v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup('a', 13),
        tup('b', 42),
        tup('c', 5)
  }}));
}

} // namespace impure

} // namespace xform
} // namespace atria
