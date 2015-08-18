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
#include <atria/xform/transducer/chain.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

#define ABL_MAKE_GCC_CRASH 0

#if ABL_MAKE_GCC_CRASH \
  || !defined(__GNUC__) \
  || defined(__clang__ ) \
  || defined(__llvm__)

TEST(chain, append)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5 }));
}

TEST(chain, variadic)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2, v1), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5, 1, 2 }));
}

TEST(chain, no_chaining_if_no_input)
{
  // Again, this is a limitation of the current approach to pure
  // stateful transducers
  auto v1 = std::vector<int> {};
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2), v1);
  EXPECT_EQ(res, (std::vector<int> {}));
}

TEST(chainl, prepend)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2), v1);
  EXPECT_EQ(res, (std::vector<int> { 13, 42, 5, 1, 2 }));
}

TEST(chainl, variadic)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2, v1), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5, 1, 2 }));
}

TEST(chainl, no_chaining_if_no_input)
{
  // Again, this is a limitation of the current approach to pure
  // stateful transducers
  auto v1 = std::vector<int> {};
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2), v1);
  EXPECT_EQ(res, (std::vector<int> {}));
}

#endif // ABL_MAKE_GCC_CRASH

} // namespace xform
} // namespace atria
