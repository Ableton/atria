// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#include <atria/meta/concept.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/distinct.hpp>
#include <atria/xform/transducer/cycle.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

TEST(distinct, into)
{
  auto v = std::vector<int> { 1, 2, 1, 3, 2, 1 };
  auto res = into_vector(distinct, v);
  EXPECT_EQ(res, (decltype(res) { 1, 2, 3 }));
}

TEST(distinct, variadic)
{
  using tup = std::tuple<int, char>;
  auto v = std::vector<int> { 1, 2, 1, 3, 2, 1, 2 };
  auto res = into_vector(comp(cycle(std::string("ab")), distinct), v);

  EXPECT_EQ(res, (decltype(res) {
        tup(1, 'a'),
        tup(2, 'b'),
        tup(3, 'b'),
        tup(2, 'a'),
        tup(1, 'b')
    }));
}

} // namespace xform
} // namespace atria
