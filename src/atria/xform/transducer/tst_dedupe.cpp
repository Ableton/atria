// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#include <atria/meta/concept.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/dedupe.hpp>
#include <atria/xform/transducer/cycle.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

#define ABL_MAKE_GCC_CRASH 0

#if ABL_MAKE_GCC_CRASH \
  || !defined(__GNUC__) \
  || defined(__clang__ ) \
  || defined(__llvm__)

TEST(dedupe, into)
{
  auto v = std::vector<int> { 1, 1, 2, 1, 1, 3, 2, 2, 2, 1 };
  auto res = into_vector(dedupe, v);
  EXPECT_EQ(res, (decltype(res) { 1, 2, 1, 3, 2, 1 }));
}

TEST(dedupe, variadic)
{
  using tup = std::tuple<int, char>;
  auto v = std::vector<int> { 1, 2, 1, 1, 1, 1, 1 };
  auto res = into_vector(comp(cycle(std::string("aabb")), dedupe), v);

  EXPECT_EQ(res, (decltype(res) {
        tup(1, 'a'),
        tup(2, 'a'),
        tup(1, 'b'),
        tup(1, 'a'),
        tup(1, 'b')
    }));
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
