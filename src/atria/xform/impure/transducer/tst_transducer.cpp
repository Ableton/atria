// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/impure/into.hpp>
#include <atria/xform/impure/transducer/take.hpp>
#include <atria/xform/impure/transducer/transducer.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {
namespace impure {

TEST(transducer_impure, type_erasure)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };
  auto xform = impure::transducer<int>{};

  {
    xform = map([] (int x) { return x + 2; });
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 3, 4, 5, 6 }));
  }

  {
    xform = filter([] (int x) { return x % 2; });
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 3 }));
  }

  {
    xform = impure::take(3);
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  }
}

} // namespace impure
} // namespace xform
} // namespace atria
