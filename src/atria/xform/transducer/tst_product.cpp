// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/product.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(product, product)
{
  using tup = std::tuple<int, int>;
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 4, 5 };
  auto res = into_vector(product(v2), v1);
  EXPECT_EQ(res, (decltype(res) {
        tup(1, 4), tup(1, 5), tup(2, 4), tup(2, 5) }));
}

TEST(product, variadic)
{
  using tup = std::tuple<int, int, char>;
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 4, 5 };
  auto v3 = std::vector<char> { 'a', 'b' };

  auto res = into_vector(product(v2, v3), v1);
  EXPECT_EQ(res, (decltype(res) {
        tup(1, 4, 'a'), tup(1, 4, 'b'), tup(1, 5, 'a'), tup(1, 5, 'b'),
        tup(2, 4, 'a'), tup(2, 4, 'b'), tup(2, 5, 'a'), tup(2, 5, 'b')
   }));
}

TEST(product, generator)
{
  using tup = std::tuple<int, int>;
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 4, 5 };

  auto res = into_vector(comp(take(1), product(v1, v2)));
  EXPECT_EQ(res, (decltype(res) {
        tup(1, 4), tup(1, 5), tup(2, 4), tup(2, 5) }));
}

} // namespace xform
} // namespace atria
