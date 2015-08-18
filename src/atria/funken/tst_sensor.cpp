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

#include <atria/funken/commit.hpp>
#include <atria/funken/concepts.hpp>
#include <atria/funken/sensor.hpp>
#include <atria/funken/watch.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace funken {

struct counter
{
  std::size_t count = 0;
  std::size_t operator() ()
  {
    return count++;
  }
};

TEST(sensor, concepts)
{
  EXPECT_TRUE(meta::check<In_value_spec(sensor<counter>)>());
  EXPECT_TRUE(meta::check<Root_value_spec(sensor<counter>)>());
  EXPECT_FALSE(Out_value<sensor<counter>>());
}

TEST(sensor, basic)
{
  auto x = make_sensor([] { return 42; });
  EXPECT_EQ(42, x.get());
  commit(x);
  EXPECT_EQ(42, x.get());
}

TEST(sensor, looks_up_only_on_commit)
{
  auto x = make_sensor(counter{});
  EXPECT_EQ(0, x.get());
  EXPECT_EQ(0, x.get());
  commit(x);
  EXPECT_EQ(1, x.get());
  EXPECT_EQ(1, x.get());
  commit(x);
  EXPECT_EQ(2, x.get());
}

TEST(sensor, watching)
{
  auto expected_old = 0;
  auto expected_curr = 1;
  auto x = make_sensor(counter{});
  auto s = testing::spy([&](std::size_t old, std::size_t curr) {
      EXPECT_EQ(expected_old, old);
      EXPECT_EQ(expected_curr, curr);
    });
  watch(x, s);
  EXPECT_EQ(0, s.count());
  commit(x);
  EXPECT_EQ(1, s.count());
  ++expected_curr, ++expected_old;
  commit(x);
  EXPECT_EQ(2, s.count());
}

} // namespace funken
} // namespace atria
