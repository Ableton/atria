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

#include <cstdint>
#include <limits>

struct deterministic_engine
{
  std::uint64_t count = 0;
  constexpr static std::uint64_t max() {
    return std::numeric_limits<std::uint64_t>::max(); }
  constexpr static std::uint64_t min() {
    return std::numeric_limits<std::uint64_t>::min(); }
  std::uint64_t operator() () { return count += max() / 6; }
};

#define ABL_XFORM_DEFAULT_RANDOM_ENGINE deterministic_engine

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/random_sample.hpp>
#include <atria/xform/transducer/range.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(random_sample, concept)
{
  meta::check<Transducer_spec(decltype(filter(std::less<int>{})),
                              meta::pack<int, int>)>();
}

TEST(random_sample, simple)
{
  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0.5)),
              std::plus<std::size_t>{}, std::size_t{}),
            100);


  EXPECT_EQ(transduce(
              comp(range(20), random_sample(1)),
              std::plus<std::size_t>{}, std::size_t{}),
            190);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0)),
              std::plus<std::size_t>{}, std::size_t{}),
            0);
}

TEST(random_sample, custom_generator)
{
  auto eng = deterministic_engine{};
  auto gen = [eng] () mutable { return double(eng()) * 2 / eng.max(); };

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0.5, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            36);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(1, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            100);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            0);
}

} // namespace xform
} // namespace atria
