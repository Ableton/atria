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

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/estd/functional.hpp>
#include <atria/testing/gtest.hpp>
#include <vector>

namespace atria {
namespace xform {

TEST(into, mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };
  auto res = std::vector<int> { };

  auto& res2 = into(res, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  EXPECT_EQ(&res, &res2);
}

TEST(into, non_mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> {}, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, appends)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> { 0 }, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 0, 1, 2, 3 }));
}

TEST(into, transduction)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto res = into(
    std::vector<std::string> {},
    comp(filter([] (int x) { return x % 2 == 0; }),
         map([] (int x) { return std::to_string(x); })),
    v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

TEST(into, zipping)
{
  auto v1 = std::vector<int> { 1, 2, 3, 4 };
  auto v2 = std::vector<std::string> { "a", "b" };

  using tup = std::tuple<int, std::string>;

  auto res = into(
    std::vector<tup> {},
    identity,
    v1, v2);
  EXPECT_EQ(res, (std::vector<tup> { tup(1, "a"), tup(2, "b") }));
}

} // namespace xform
} // namespace atria
