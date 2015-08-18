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

#include <atria/prelude/complement.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace prelude {

TEST(complement, compose_one_fn)
{
  auto fn = complement([](int x) { return x == 1; });
  EXPECT_FALSE(fn(1));
  EXPECT_TRUE(fn(0));
}

namespace
{

struct thingy { bool method() { return true; } };
bool free_func(int x, int y) { return x == y; }

} // anon

TEST(complement, uses_invoke)
{
  {
    auto fn = complement(&thingy::method);
    EXPECT_FALSE(fn(thingy{}));
  }
  {
    auto fn = complement(free_func);
    EXPECT_FALSE(fn(1, 1));
    EXPECT_TRUE(fn(1, 0));
  }
}

} // namespace prelude
} // namespace atria
