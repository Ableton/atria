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

#include <atria/xform/sequence.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/interleave.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/algorithm.hpp>
ABL_RESTORE_WARNINGS

#include <vector>

namespace atria {
namespace xform {

TEST(sequence, identity)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };
  auto r = std::vector<int> {};
  auto seq = sequence(identity, v);
  boost::copy(seq, std::back_inserter(r));
  EXPECT_EQ(r, v);
}

TEST(sequence, filter_map)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };
  auto r = std::vector<int> {};
  auto seq = sequence<int>(
    comp(filter([](int x) { return x % 2 == 0; }),
         map([](int x) { return x * 2; })),
    v);
  boost::copy(seq, std::back_inserter(r));
  EXPECT_EQ(r, (std::vector<int> {{4, 8}}));
}

TEST(sequence, rvalues)
{
  auto r = std::vector<int> {};
  boost::copy(
    sequence(identity, std::vector<int> { 1, 2, 3, 4 }),
    std::back_inserter(r));
  EXPECT_EQ(r, (std::vector<int> { 1, 2, 3, 4 }));
}

TEST(sequence, constant)
{
  const auto v = std::vector<int> { 1, 2, 3, 4 };
  auto r = std::vector<int> {};
  boost::copy(
    sequence(identity, v),
    std::back_inserter(r));
  EXPECT_EQ(r, v);
}

TEST(sequence, no_shared_iterator_state)
{
  const auto v = std::vector<int> { 1, 2, 3, 4  };
  auto seq = sequence(take(3), v);

  auto f = seq.begin();
  auto l = seq.end();
  auto f2 = f++;

  auto r1 = std::vector<int> {};
  std::copy(f2, l, std::back_inserter(r1));
  EXPECT_EQ(r1, (decltype(r1) { 1, 2, 3 }));

  auto r2 = std::vector<int> {};
  std::copy(f, l, std::back_inserter(r2));
  EXPECT_EQ(r2, (decltype(r2) { 2, 3 }));
}

TEST(sequence, empty)
{
  const auto v = std::vector<int> {};
  auto seq = sequence(take(3), v);
  auto r = std::vector<int> {};
  boost::copy(seq, std::back_inserter(r));
  EXPECT_EQ(r, (decltype(r) {}));
}

TEST(sequence, variadic_growing_no_type_deduction)
{
  using res_t = eggs::variant<int, std::string>;

  const auto v1 = std::vector<int> { 1, 2, 3, 4};
  const auto v2 = std::vector<std::string> { "a", "b", "c" };
  auto seq = sequence<res_t>(interleave, v1, v2);

  auto r = std::vector<res_t> {};
  boost::copy(seq, std::back_inserter(r));
  EXPECT_EQ(r, (decltype(r) {
        res_t{1}, res_t{"a"},
        res_t{2}, res_t{"b"},
        res_t{3}, res_t{"c"} }));
}

TEST(sequence, generator)
{
  auto seq = sequence(enumerate);

  auto r = std::vector<std::size_t> {};
  std::copy_n(seq.begin(), 4u, std::back_inserter(r));
  EXPECT_EQ(r, (decltype(r) {0u, 1u, 2u, 3u}));
}

} // namespace xform
} // namespace atria
