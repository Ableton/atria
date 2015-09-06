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

#include <atria/xform/config.hpp>
#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/take_nth.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

#if ABL_MAKE_GCC_CRASH

TEST(take_nth, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(decltype(take_nth(42)))>();
}

TEST(take_nth, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  {
    auto res = into(std::vector<int>{}, take_nth(1), v);
    EXPECT_EQ(res, (decltype(res) { 1, 2, 3, 4, 5 }));
  }

  {
    auto res = into(std::vector<int>{}, take_nth(2), v);
    EXPECT_EQ(res, (decltype(res) { 1, 3, 5 }));
  }

  {
    auto res = into(std::vector<int>{}, take_nth(3), v);
    EXPECT_EQ(res, (decltype(res) { 1, 4 }));
  }
}

TEST(take_nth, compose)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto res = into_vector(comp(take_nth(2), take(2)), v);
  EXPECT_EQ(res, (decltype(res) { 1, 3 }));
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
