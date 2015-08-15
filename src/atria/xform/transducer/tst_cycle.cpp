// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/cycle.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(cycle, generator)
{
  using tup = std::tuple<int, int>;
  auto v1 = std::vector<int> { 13, 42, 5, 6, 15 };
  auto v2 = std::vector<int> { 0, 1 };
  auto res = into_vector(cycle(v2), v1);
  EXPECT_EQ(res, (decltype(res) {
        tup(13, 0),
        tup(42, 1),
        tup(5, 0),
        tup(6, 1),
        tup(15, 0)
  }));
}

TEST(cycle, variadic)
{
  using tup = std::tuple<int, std::string>;
  auto v1 = std::vector<int> { 0, 1 };
  auto v2 = std::vector<std::string> { "one", "two", "three" };
  auto res = into_vector(comp(cycle(v1, v2), take(5)));
  EXPECT_EQ(res, (decltype(res) {
        tup(0, "one"),
        tup(1, "two"),
        tup(0, "three"),
        tup(1, "one"),
        tup(0, "two")
  }));
}

} // namespace xform
} // namespace atria
