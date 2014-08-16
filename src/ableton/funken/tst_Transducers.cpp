// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/estd/memory.hpp>
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

TEST(Transduce, Identity)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(transduce(identity, std::plus<int>{}, 1, v), 13);
}

TEST(Transduce, Mapping)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  EXPECT_EQ(transduce(map(times2), std::plus<int>{}, 1, v), 25);
}

TEST(Transduce, Filter)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto odd = [] (int x) { return x % 2 == 0; };
  EXPECT_EQ(transduce(filter(odd), std::plus<int>{}, 1, v), 9);
}

TEST(Transduce, Composition)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  auto odd = [] (int x) { return x % 2 == 0; };

  // Transducers compose from left to right, this is equivalent to
  // Haskell-like expression:
  //
  //   foldl (+) $ map times2 $ filter odd $ v
  //
  auto res = transduce(
    comp(filter(odd), map(times2)), std::plus<int>{}, 1, v);
  EXPECT_EQ(res, 17);
}

TEST(Transduce, Variadic)
{
  auto v1 = std::vector<int> { 1, 2, 3, 6 };
  auto v2 = std::vector<int> { 1, 2, 1, 2 };

  EXPECT_EQ(transduce(map(std::multiplies<int>{}),
                      std::plus<int>{},
                      1,
                      v1, v2),
            21);
}

} // namespace funken
} // namespace ableton
