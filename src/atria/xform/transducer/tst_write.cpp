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
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/write.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <sstream>
#include <vector>

namespace atria {
namespace xform {

#if ABL_MAKE_GCC_CRASH

TEST(write, write)
{
  auto v = std::vector<int>{ 1, 2, 3, 4 };
  auto stream = std::stringstream{};
  transduce(write(stream), first_rf, 0, v);
  EXPECT_EQ(stream.str(), "1234");
}

TEST(write, in_separator)
{
  auto v = std::vector<int>{ 1, 2, 3, 4 };
  auto stream = std::stringstream{};
  transduce(write(stream, ' '), first_rf, 0, v);
  EXPECT_EQ(stream.str(), "1 2 3 4");
}

TEST(write, in_separator_variadic_is_arg_separator)
{
  auto v1 = std::vector<int>{ 1, 2, 3, 4 };
  auto v2 = std::vector<char>{ 'y', 'e', 'a', 'h' };
  auto stream = std::stringstream{};
  transduce(write(stream, ' '), first_rf, 0, v1, v2);
  EXPECT_EQ(stream.str(), "1 y 2 e 3 a 4 h");
}

TEST(write, in_separator_and_arg_separator)
{
  auto v1 = std::vector<int>{ 1, 2, 3, 4 };
  auto v2 = std::vector<char>{ 'y', 'e', 'a', 'h' };
  auto stream = std::stringstream{};
  transduce(write(stream, ' ', ','), first_rf, 0, v1, v2);
  EXPECT_EQ(stream.str(), "1,y 2,e 3,a 4,h");
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
