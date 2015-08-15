// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/repeat.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(repeat, repeat)
{
  using tup = std::tuple<int, const char*>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(repeat("hola"), v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup(13, "hola"),
        tup(42, "hola"),
        tup(5,  "hola")
  }}));
}

TEST(repeat, generator)
{
  auto res = into_vector(comp(repeat('a'), take(3)));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'a', 'a' }}));
}

TEST(repeatn, generator)
{
  auto res = into_vector(comp(repeatn(3, 'a')));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'a', 'a' }}));
}

} // namespace xform
} // namespace atria
