// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/zip.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(zip, zip_transducer)
{
  using std::get;

  auto v1 = std::vector<int> { 13, 42, 5 };
  auto v2 = std::vector<double> { 1.1, 2.2, 3.3 };

  auto res = transduce(
    zip,
    [] (double x, std::tuple<int, double> t) {
      return x + get<0>(t) + get<1>(t);
    },
    1.0,
    v1,
    v2);

  EXPECT_DOUBLE_EQ(res, 67.6);
}

} // namespace xform
} // namespace atria
