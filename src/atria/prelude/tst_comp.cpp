// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace prelude {

TEST(comp, compose_one_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; });
  EXPECT_EQ(fn(1), 2);
  EXPECT_EQ(fn(42), 43);
}

TEST(comp, compose_two_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; });
  EXPECT_EQ(fn(3), 7);
  EXPECT_EQ(fn(42), 85);
}

TEST(comp, compose_three_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x - 1; });
  EXPECT_EQ(fn(3), 5);
  EXPECT_EQ(fn(42), 83);
}

TEST(comp, various_types)
{
  auto fn = comp(
    [](double x) { return x + 1; },
    [](std::string) { return 42.0; },
    [](int x) { return std::to_string(x); });
  EXPECT_EQ(fn(3), 43.0);
  EXPECT_EQ(fn(42), 43.0);
}

namespace
{

struct thingy
{
  int value;

  thingy& times2() { value *= 2; return *this; }
  thingy& plus2()  { value += 2; return *this; }
  int extract()    { return value; }
};

int free_func(int x, int y) { return x - y; }

} // anon

TEST(comp, uses_invoke)
{
  auto res = comp(
    &thingy::extract,
    &thingy::times2,
    &thingy::plus2,
    [](int x) { return thingy{x}; },
    free_func);
  EXPECT_EQ(res(10, 5), 14);
}

} // namespace prelude
} // namespace atria
