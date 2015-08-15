// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/prelude/complement.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace prelude {

TEST(complement, compose_one_fn)
{
  auto fn = complement([](int x) { return x == 1; });
  EXPECT_FALSE(fn(1));
  EXPECT_TRUE(fn(0));
}

namespace
{

struct thingy { bool method() { return true; } };
bool free_func(int x, int y) { return x == y; }

} // anon

TEST(complement, uses_invoke)
{
  {
    auto fn = complement(&thingy::method);
    EXPECT_FALSE(fn(thingy{}));
  }
  {
    auto fn = complement(free_func);
    EXPECT_FALSE(fn(1, 1));
    EXPECT_TRUE(fn(1, 0));
  }
}

} // namespace prelude
} // namespace atria
