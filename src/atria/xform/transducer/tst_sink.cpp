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
#include <atria/xform/run.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/transducer/sink.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(sink, sink)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto r = std::vector<int> {};
  run(sink([&](int x) { r.push_back(x); }), v);
  EXPECT_EQ(v, r);
}

TEST(sink, moves_values_out_of_rvalue_container)
{
  using elem = testing::copy_spy<>;

  auto x = elem{};
  auto v = std::vector<elem> { x, x, x, x };
  auto copies = x.copied.count();

  auto r = into_vector(comp(sink([](elem){}), enumerate), std::move(v));

  EXPECT_EQ(x.copied.count(), copies);
  EXPECT_EQ(r, (decltype(r) {0, 1, 2, 3}));
}

} // namespace xform
} // namespace atria
