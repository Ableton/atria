//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

namespace test_detail {

struct to_string_t { std::string operator() (int x); };
struct stoi_t { int operator() (std::string x); };

} // namespace test_detail

TEST(into_vector, type_deduction)
{
  using namespace test_detail;

  static_assert(
    std::is_same<std::vector<int>,
                 decltype(into_vector(identity,
                                      std::vector<int>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<std::tuple<int, std::string>>,
                 decltype(into_vector(identity,
                                      std::vector<int>{},
                                      std::vector<std::string>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<std::string>,
                 decltype(into_vector(map(to_string_t{}),
                                      std::vector<int>{}))>{}, "");
  static_assert(
    std::is_same<std::vector<int>,
                 decltype(into_vector(map(stoi_t{}),
                                      std::vector<std::string>{}))>{}, "");
}

TEST(into_vector, zipping)
{
  auto v1 = std::vector<int> { 1, 2, 3, 4 };
  auto v2 = std::vector<std::string> { "a", "b" };
  using tup = std::tuple<int, std::string>;

  auto res = into_vector(identity, v1, v2);
  EXPECT_EQ(res, (std::vector<tup> { tup(1, "a"), tup(2, "b") }));
}

#if ABL_MAKE_GCC_CRASH

TEST(into_vector, transduction)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto xform = comp(
    filter([] (int x) { return x % 2 == 0; }),
    map([] (int x) { return std::to_string(x); }));
  auto res = into_vector(xform, v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

TEST(into_vector, type_erasure)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto xform = transducer<int, std::string> {
    comp(
      filter([] (int x) { return x % 2 == 0; }),
      map([] (int x) { return std::to_string(x); }))
  };
  auto res = into_vector(xform, v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
