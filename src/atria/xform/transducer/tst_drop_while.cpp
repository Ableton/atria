// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/drop_while.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

TEST(drop_while, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(
   decltype(drop_while(std::bind(estd::less<>{}, 42, _1))))>();
}

TEST(drop_while, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 3 };

  {
    auto lt0 = std::bind(estd::less<>{}, _1, 0);
    auto res = into_vector(drop_while(lt0), v);
    EXPECT_EQ(res, (decltype(res) { 1, 2, 3, 4, 3 }));
  }

  {
    auto lt4 = std::bind(estd::less<>{}, _1, 4);
    auto res = into_vector(drop_while(lt4), v);
    EXPECT_EQ(res, (decltype(res) { 4, 3 }));
  }

  {
    auto lt5 = std::bind(estd::less<>{}, _1, 5);
    auto res = into_vector(drop_while(lt5), v);
    EXPECT_EQ(res, (decltype(res) {}));
  }
}

TEST(drop_while, compose)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto lt3 = std::bind(estd::less<>{}, _1, 3);
  auto res = into_vector(comp(drop_while(lt3), take(2)), v);
  EXPECT_EQ(res, (decltype(res) { 3, 4 }));
}

} // namespace xform
} // namespace atria
