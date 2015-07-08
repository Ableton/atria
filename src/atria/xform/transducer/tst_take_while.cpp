// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/take_while.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(take_while, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(
    decltype(take_while(std::bind(estd::less<>{}, 42, _1))))>();
}

TEST(take_while, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto pred = std::bind(estd::less<>{}, _1, 4);

  auto res = into_vector(take_while(pred), v);
  EXPECT_EQ(res, (decltype(res) { 1, 2, 3 }));
}

} // namespace xform
} // namespace atria
