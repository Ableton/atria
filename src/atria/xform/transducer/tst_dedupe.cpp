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

#include <atria/meta/concept.hpp>
#include <atria/xform/config.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/dedupe.hpp>
#include <atria/xform/transducer/cycle.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

#if ABL_MAKE_GCC_CRASH

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
