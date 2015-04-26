// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/estd/memory.hpp>
#include <atria/xform/transducers.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(compose, compose_one_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; });
  EXPECT_EQ(fn(1), 2);
  EXPECT_EQ(fn(42), 43);
}

TEST(compose, compose_two_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; });
  EXPECT_EQ(fn(3), 7);
  EXPECT_EQ(fn(42), 85);
}

TEST(compose, compose_three_fn)
{
  auto fn = comp(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x - 1; });
  EXPECT_EQ(fn(3), 5);
  EXPECT_EQ(fn(42), 83);
}

TEST(compose, various_types)
{
  auto fn = comp(
    [](double x) { return x + 1; },
    [](std::string) { return 42.0; },
    [](int x) { return std::to_string(x); });
  EXPECT_EQ(fn(3), 43.0);
  EXPECT_EQ(fn(42), 43.0);
}

TEST(transduce, identity)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(transduce(identity, std::plus<int>{}, 1, v), 13);
}

TEST(transduce, mapping)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  EXPECT_EQ(transduce(map(times2), std::plus<int>{}, 1, v), 25);
}

TEST(transduce, composition)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  auto odd = [] (int x) { return x % 2 == 0; };

  // transducers compose from left to right, this is equivalent to
  // Haskell-like expression:
  //
  //   foldl (+) $ map times2 $ filter odd $ v
  //
  auto res = transduce(
    comp(filter(odd), map(times2)), std::plus<int>{}, 1, v);
  EXPECT_EQ(res, 17);
}

TEST(transduce, variadic)
{
  auto v1 = std::vector<int> { 1, 2, 3, 6 };
  auto v2 = std::vector<int> { 1, 2, 1, 2 };

  EXPECT_EQ(transduce(map(std::multiplies<int>{}),
                      std::plus<int>{},
                      1,
                      v1, v2),
            21);
}

TEST(into, mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };
  auto res = std::vector<int> { };

  auto& res2 = into(res, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  EXPECT_EQ(&res, &res2);
}

TEST(into, non_mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> {}, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, appends)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> { 0 }, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 0, 1, 2, 3 }));
}

TEST(into, transduction)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto res = into(
    std::vector<std::string> {},
    comp(filter([] (int x) { return x % 2 == 0; }),
         map([] (int x) { return std::to_string(x); })),
    v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

TEST(into, zipping)
{
  auto v1 = std::vector<int> { 1, 2, 3, 4 };
  auto v2 = std::vector<std::string> { "a", "b" };

  using tup = std::tuple<int, std::string>;

  auto res = into(
    std::vector<tup> {},
    identity,
    v1, v2);
  EXPECT_EQ(res, (std::vector<tup> { tup(1, "a"), tup(2, "b") }));
}

TEST(into, cat)
{
  auto v = std::vector<std::vector<int>> { { 1, 2 }, { 3 }, { 4, 5, 6 } };

  auto res = into(std::vector<int> {}, cat, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3, 4, 5, 6 }));
}

TEST(into, mapcat)
{
  auto v = std::vector<std::vector<int>> { { 1, 2 }, { 3 }, { 4, 5, 6 } };

  auto res = into(std::vector<int> {}, mapcat([](int x) { return x * 2; }), v);
  EXPECT_EQ(res, (std::vector<int> { 2, 4, 6, 8, 10, 12 }));
}

TEST(into, take)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<int> {}, take(3), v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, take_stops_early_enough)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(
    std::vector<int> {},
    comp(
      map([](int x) {
          if (x > 4)
            throw std::runtime_error("bad!");
          return x;
        }),
      take(3)),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, take_stops_early_enough2)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(
    std::vector<int> {},
    comp(
      take(3),
      map([](int x) {
          if (x > 4)
            throw std::runtime_error("bad!");
          return x;
        })),
    v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

} // namespace xform
} // namespace atria
