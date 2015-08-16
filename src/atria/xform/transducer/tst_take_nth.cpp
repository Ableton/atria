// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/take_nth.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

#define ABL_MAKE_GCC_CRASH 0

#if ABL_MAKE_GCC_CRASH \
  || !defined(__GNUC__) \
  || defined(__clang__ ) \
  || defined(__llvm__)

TEST(take_nth, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(decltype(take_nth(42)))>();
}

TEST(take_nth, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  {
    auto res = into(std::vector<int>{}, take_nth(1), v);
    EXPECT_EQ(res, (decltype(res) { 1, 2, 3, 4, 5 }));
  }

  {
    auto res = into(std::vector<int>{}, take_nth(2), v);
    EXPECT_EQ(res, (decltype(res) { 1, 3, 5 }));
  }

  {
    auto res = into(std::vector<int>{}, take_nth(3), v);
    EXPECT_EQ(res, (decltype(res) { 1, 4 }));
  }
}

TEST(take_nth, compose)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto res = into_vector(comp(take_nth(2), take(2)), v);
  EXPECT_EQ(res, (decltype(res) { 1, 3 }));
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
