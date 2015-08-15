// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/iter.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(iter, generator)
{
  auto v = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(iter(v));
  EXPECT_EQ(res, (std::vector<int> { 13, 42, 5 }));
}

TEST(iter, variadic)
{
  auto v1 = std::vector<int> { 13, 42, 5, 6, 7 };
  auto v2 = std::vector<std::string> { "one", "two", "three" };
  auto res = into_vector(iter(v1, v2));
  EXPECT_EQ(res, (decltype(res) {
        std::make_tuple(13, "one"),
        std::make_tuple(42, "two"),
        std::make_tuple(5,  "three")
  }));
}

} // namespace xform
} // namespace atria
