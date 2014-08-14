// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/funken/Transducers.hpp>
#include <gtest/gtest.h>

namespace ableton {
namespace funken {

TEST(Compose, ComposeOneFn)
{
  auto fn = comp(
    [](int x) { return x + 1; });
  EXPECT_EQ(fn(1), 2);
  EXPECT_EQ(fn(42), 43);
}

TEST(Compose, ComposeTwoFn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; });
  EXPECT_EQ(fn(3), 7);
  EXPECT_EQ(fn(42), 85);
}

TEST(Compose, ComposeThreeFn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x - 1; });
  EXPECT_EQ(fn(3), 5);
  EXPECT_EQ(fn(42), 83);
}

TEST(Compose, VariousTypes)
{
  auto fn = comp(
    [](double x) { return x + 1; },
    [](std::string x) { return 42.0; },
    [](int x) { return std::to_string(x); });
  EXPECT_EQ(fn(3), 43.0);
  EXPECT_EQ(fn(42), 43.0);
}

} // namespace funken
} // namespace ableton
