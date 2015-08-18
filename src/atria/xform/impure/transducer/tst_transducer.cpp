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

#include <atria/xform/concepts.hpp>
#include <atria/xform/impure/into.hpp>
#include <atria/xform/impure/transducer/take.hpp>
#include <atria/xform/impure/transducer/transducer.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {
namespace impure {

TEST(transducer_impure, type_erasure)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };
  auto xform = impure::transducer<int>{};

  {
    xform = map([] (int x) { return x + 2; });
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 3, 4, 5, 6 }));
  }

  {
    xform = filter([] (int x) { return x % 2; });
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 3 }));
  }

  {
    xform = impure::take(3);
    auto res = impure::into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  }
}

} // namespace impure
} // namespace xform
} // namespace atria
