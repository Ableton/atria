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

#include <atria/xform/run.hpp>
#include <atria/xform/transducer/read.hpp>
#include <atria/xform/transducer/write.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <sstream>
#include <vector>

namespace atria {
namespace xform {

#if ABL_MAKE_GCC_CRASH

TEST(run, nullary)
{
  auto input = std::stringstream{"1 2 3 4 5"};
  auto output = std::stringstream{};

  run(comp(read<int>(input), write(output, ';')));
  EXPECT_EQ(output.str(), "1;2;3;4;5;");
}

TEST(run, unary)
{
  auto v = std::vector<int>{1, 2, 3, 4, 5};
  auto output = std::stringstream{};

  run(write(output, ';'), v);
  EXPECT_EQ(output.str(), "1;2;3;4;5;");
}

TEST(run, variadic)
{
  auto v1 = std::vector<int>{1, 2, 3, 4, 5};
  auto v2 = std::vector<char>{'h', 'e', 'l', 'l', 'o'};
  auto output = std::stringstream{};

  run(write(output, ';', ' '), v1, v2);
  EXPECT_EQ(output.str(), "1 h;2 e;3 l;4 l;5 o;");
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
