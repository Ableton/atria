// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/drop.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

TEST(drop, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(
   decltype(drop(std::bind(estd::less<>{}, 42, _1))))>();
}

TEST(drop, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  {
    auto res = into_vector(drop(0), v);
    EXPECT_EQ(res, (decltype(res) { 1, 2, 3, 4, 5 }));
  }

  {
    auto res = into_vector(drop(2), v);
    EXPECT_EQ(res, (decltype(res) { 3, 4, 5 }));
  }

  {
    auto res = into_vector(drop(6), v);
    EXPECT_EQ(res, (decltype(res) {}));
  }
}

TEST(drop, compose)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto res = into_vector(comp(drop(2), take(2)), v);
  EXPECT_EQ(res, (decltype(res) { 3, 4 }));
}

} // namespace xform
} // namespace atria
