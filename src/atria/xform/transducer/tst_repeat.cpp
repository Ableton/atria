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
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/repeat.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(repeat, repeat)
{
  using tup = std::tuple<int, const char*>;
  auto v = std::vector<int> { 13, 42, 5 };

  auto res = into_vector(repeat("hola"), v);
  EXPECT_EQ(res, (std::vector<tup> {{
        tup(13, "hola"),
        tup(42, "hola"),
        tup(5,  "hola")
  }}));
}

TEST(repeat, generator)
{
  auto res = into_vector(comp(repeat('a'), take(3)));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'a', 'a' }}));
}

TEST(repeatn, generator)
{
  auto res = into_vector(comp(repeatn(3, 'a')));
  EXPECT_EQ(res, (std::vector<char> {{ 'a', 'a', 'a' }}));
}

} // namespace xform
} // namespace atria
