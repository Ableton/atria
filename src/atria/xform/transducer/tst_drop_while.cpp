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

/*!
 * @file
 */

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

namespace {
bool free_lt4(int x) { return x < 4; }
} // anonymous

TEST(drop_while, invoke)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 3 };
  auto res = into_vector(drop_while(free_lt4), v);
  EXPECT_EQ(res, (decltype(res) { 4, 3 }));
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
