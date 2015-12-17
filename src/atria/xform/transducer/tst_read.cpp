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
#include <atria/xform/transducer/read.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>
#include <sstream>

namespace atria {
namespace xform {

TEST(read, into)
{
  auto stream = std::stringstream{"1 2 3 4 5 6"};
  auto res = into_vector(read<int>(stream));
  EXPECT_EQ(res, (decltype(res) {
        1, 2, 3, 4, 5, 6 }));
}

TEST(read, into_variadic)
{
  using tup = std::tuple<int, std::string>;

  auto stream = std::stringstream{"1 hello 2 my 3 friend 4 !!"};
  auto res = into_vector(read<int, std::string>(stream));
  EXPECT_EQ(res, (decltype(res) {
        tup(1, "hello"), tup(2, "my"), tup(3, "friend"), tup(4, "!!") }));
}

TEST(read, into_ends_on_bad_input)
{
  auto stream = std::stringstream{"1 2 3 fuck 4 5 6"};
  auto res = into_vector(read<int>(stream));
  EXPECT_EQ(res, (decltype(res) {
        1, 2, 3 }));
}

} // namespace xform
} // namespace atria
