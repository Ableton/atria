// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

namespace test_detail {

struct to_string_t { std::string operator() (int x); };
struct stoi_t { int operator() (std::string x); };

} // namespace test_detail

TEST(into_vector, type_deduction)
{
  using namespace test_detail;

  static_assert(
    std::is_same<std::vector<int>,
                 decltype(into_vector(identity,
                                      std::vector<int>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<std::tuple<int, std::string>>,
                 decltype(into_vector(identity,
                                      std::vector<int>{},
                                      std::vector<std::string>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<std::string>,
                 decltype(into_vector(map(to_string_t{}),
                                      std::vector<int>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<int>,
                 decltype(into_vector(map(stoi_t{}),
                                      std::vector<std::string>{}))>{}, "");
}

TEST(into_vector, transduction)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto xform = comp(
    filter([] (int x) { return x % 2 == 0; }),
    map([] (int x) { return std::to_string(x); }));
  auto res = into_vector(xform, v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

TEST(into_vector, zipping)
{
  auto v1 = std::vector<int> { 1, 2, 3, 4 };
  auto v2 = std::vector<std::string> { "a", "b" };
  using tup = std::tuple<int, std::string>;

  auto res = into_vector(identity, v1, v2);
  EXPECT_EQ(res, (std::vector<tup> { tup(1, "a"), tup(2, "b") }));
}

} // namespace xform
} // namespace atria
