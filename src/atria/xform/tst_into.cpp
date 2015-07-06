// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>

#include <atria/estd/functional.hpp>
#include <atria/testing/gtest.hpp>
#include <vector>

namespace atria {
namespace xform {

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

} // namespace xform
} // namespace atria
