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

#include <atria/xform/reductor.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(reductor, reductor)
{
  auto r = reductor(estd::plus<>{}, 0, 1);
  r(2);
  r(3);
  r(4);
  EXPECT_EQ(r.complete(), 10);
}

TEST(reductor, empty_reductor)
{
  auto r = empty_reductor<int>(estd::plus<>{}, 0);
  r(2);
  r(3);
  r(4);
  EXPECT_EQ(r.complete(), 9);
}

TEST(reductor, reductor_no_move)
{
  auto r = reductor(estd::plus<>{}, std::string{}, "");
  r("hello");
  r(" ");
  r("world");
  EXPECT_EQ(r.complete(), "hello world");
  EXPECT_EQ(r.complete(), "hello world");
}

TEST(reductor, reductor_chaining)
{
  auto result = reductor(estd::plus<>{}, std::string{}, "")
    ("hello")(" ")("my")(" ")("friend")("!")
    .complete();
  EXPECT_EQ(result, "hello my friend!");
}

TEST(reductor, reductor_move)
{
  auto s = testing::copy_spy<>{};
  auto r = reductor(first_rf, std::move(s), 0);
  r(1);
  r(2);
  r(3);
  auto c = std::move(r).complete();
  EXPECT_EQ(c.copied.count(), 0);
}

TEST(reductor, generator)
{
  auto r = reductor(enumerate(last_rf), -1);
  EXPECT_EQ(r.complete(), 0);
  r();
  EXPECT_EQ(r.complete(), 1);
  r();
  EXPECT_EQ(r.complete(), 2);
}

TEST(reductor, generator_empty)
{
  auto r = empty_reductor(enumerate(last_rf), std::size_t{42});
  EXPECT_EQ(r.complete(), 42u);
  r();
  EXPECT_EQ(r.complete(), 0u);
  r();
  EXPECT_EQ(r.complete(), 1u);
}

TEST(reductor, termination)
{
  auto r = reductor(take(4)(enumerate(last_rf)), 0);
  EXPECT_TRUE(r());
  EXPECT_TRUE(r());
  EXPECT_FALSE(r());
  EXPECT_FALSE(r);
}

TEST(reductor, termination_empty)
{
  auto r = empty_reductor(take(4)(enumerate(last_rf)), 0);
  EXPECT_TRUE(r());
  EXPECT_TRUE(r());
  EXPECT_TRUE(r());
  EXPECT_FALSE(r());
  EXPECT_FALSE(r);
}

TEST(reductor, current)
{
  auto r = empty_reductor(take(4)(enumerate(last_rf)), std::size_t{0});
  EXPECT_TRUE(r());
  EXPECT_EQ(r.current(), 0);
  r.current(std::size_t{10});
  EXPECT_EQ(r.current(), 10);
  EXPECT_TRUE(r());
  EXPECT_EQ(r.current(), 1);
  EXPECT_TRUE(r());
  EXPECT_EQ(r.current(), 2);
  EXPECT_FALSE(r());
  EXPECT_FALSE(r);
}

TEST(reductor, constant)
{
  const auto r1 = reductor(enumerate(last_rf), 0);
  const auto r2 = r1();
  const auto r2_ = r1();
  const auto r3 = r2();

  EXPECT_EQ(r2.complete(), 1);
  EXPECT_EQ(r2_.complete(), 1);
  EXPECT_EQ(r3.complete(), 2);
}

} // namespace xform
} // namespace atria
