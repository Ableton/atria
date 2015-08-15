// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/map_indexed.hpp>
#include <atria/testing/gtest.hpp>
#include <string>

namespace atria {
namespace xform {

TEST(map_indexed, mapping)
{
  auto v = std::vector<std::string> { "1", "2", "3", "6" };
  auto timesi = [] (std::string x, std::size_t index) {
    return std::stoi(x) * static_cast<int>(index);
  };
  EXPECT_EQ(transduce(map_indexed(timesi), std::plus<int>{}, 1, v), 27);
}

} // namespace xform
} // namespace atria
