// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#include <atria/meta/concept.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/interpose.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

TEST(interpose, into)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto res = into_vector(interpose(42), v);
  EXPECT_EQ(res, (decltype(res) { 1, 42, 2, 42, 3, 42, 4, 42, 5 }));
}

TEST(interpose, termination)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto res = into_vector(comp(interpose(42), take(4)), v);
  EXPECT_EQ(res, (decltype(res) { 1, 42, 2, 42 }));
}

TEST(interpose, variadic)
{
  using tup = std::tuple<int, char>;
  auto v1 = std::vector<int> { 1, 2, 3, 4, 5 };
  auto v2 = std::vector<char> { 'a', 'b', 'c' };

  auto res = into_vector(interpose(42, 'Z'), v1, v2);
  EXPECT_EQ(res, (decltype(res) {
        tup(1, 'a'),
        tup(42, 'Z'),
        tup(2, 'b'),
        tup(42, 'Z'),
        tup(3, 'c')
      }));
}

} // namespace xform
} // namespace atria
