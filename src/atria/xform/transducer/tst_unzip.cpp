// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/unzip.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/xform/reducing/first_rf.hpp>

#include <atria/testing/gtest.hpp>
#include <iostream>

namespace atria {
namespace xform {

TEST(unzip, unzip_transducer)
{
  using tup = std::tuple<int, double>;

  auto v1 = std::vector<tup> {{ tup(13, 1.1), tup(42, 2.2), tup(5, 3.3) }};

  auto res = transduce(
    unzip,
    [] (double x, int y, double z) {
      return x + y + z;
    },
    1.0,
    v1);

  EXPECT_DOUBLE_EQ(res, 67.6);
}

TEST(unzip, unzip_transducer_variadic_multitype)
{
  using tup1 = std::tuple<int, double>;
  using tup2 = std::tuple<char>;
  using arr  = std::array<int, 2>;

  auto v1 = std::vector<tup1> {{ tup1(13, 1.1), tup1(42, 2.2), tup1(5, 3.3) }};
  auto v2 = std::vector<short> {{ 1, 2, 3}};
  auto v3 = std::vector<tup2> {{ tup2('a'), tup2('b'), tup2('c') }};
  auto v4 = std::vector<arr> {{ arr{{1, 2}}, arr{{3, 4}}, arr{{5, 6}} }};

  auto res = transduce(
    unzip,
    [] (double x, int y, double z, short v, char w, int a, int b) {
      return x + y + z + v + w + a + b;
    },
    1.0,
    v1, v2, v3, v4);

  EXPECT_DOUBLE_EQ(res, 388.6);
}

} // namespace xform
} // namespace atria
