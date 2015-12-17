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
#include <atria/xform/any_state.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(state_traits, concept)
{
  meta::check<State_spec(int)>();
  meta::check<State_spec(state_wrapper<no_tag, int, int>)>();
  meta::check<State_spec(any_state)>();
}

TEST(state_traits, unwrap_all_wrap_state)
{
  EXPECT_EQ(state_unwrap_all(42), 42);
  EXPECT_EQ(state_unwrap_all(wrap_state(42, {})), 42);
  EXPECT_EQ(state_unwrap_all(wrap_state(wrap_state(42, {}), "")), 42);
}

TEST(state_traits, unwrap_all_skip_state)
{
  auto odd = [] (int x) { return x % 2; };
  auto rf = comp(filter(odd), take(10))(last_rf);

  auto s = rf(int{}, 41);
  EXPECT_EQ(state_unwrap_all(s), 41);
  s = rf(s, 13);
  EXPECT_EQ(state_unwrap_all(s), 13);
}

TEST(state_traits, unwrap_all_type_erased)
{
  auto rf = transducer<int>{identity} (last_rf);

  auto s = rf(int{}, 41);
  EXPECT_EQ(state_unwrap_all(s), 41);
  s = rf(s, 13);
  EXPECT_EQ(state_unwrap_all(s), 13);
}

TEST(state_traits, unwrap_all_complex)
{
  auto odd = [] (int x) { return x % 2; };
  auto rf = transducer<int>{comp(filter(odd), take(10))} (last_rf);

  auto s = rf(int{}, 41);
  EXPECT_EQ(state_unwrap_all(s), 41);
  s = rf(s, 13);
  EXPECT_EQ(state_unwrap_all(s), 13);
}

TEST(state_traits, unwrap_all_moar_complex)
{
  auto odd = [] (std::size_t x) { return x % 2; };
  auto rf = transducer<meta::pack<>, std::size_t>{
    comp(enumerate, filter(odd), take(10))} (last_rf);

  auto s = rf(std::size_t{});
  EXPECT_EQ(state_unwrap_all(s), 0);
  s = rf(s);
  EXPECT_EQ(state_unwrap_all(s), 1);
  s = rf(s);
  EXPECT_EQ(state_unwrap_all(s), 1);
  s = rf(s);
  EXPECT_EQ(state_unwrap_all(s), 3);
}

TEST(state_traits, rewrap_wrap_state)
{
  struct t1 : meta::pack<t1> {};
  struct t2 : meta::pack<t2> {};
  EXPECT_EQ(state_rewrap(42, 13),
            13);
  EXPECT_EQ(state_rewrap(wrap_state<t1>(42, {}), 13),
            wrap_state<t1>(13, {}));
  EXPECT_EQ(state_rewrap(wrap_state<t2>(wrap_state<t1>(42, {}), ""), 13),
            wrap_state<t2>(wrap_state<t1>(13, {}), ""));
}

TEST(state_traits, rewrap_skip_state)
{
  auto odd = [] (int x) { return x % 2; };
  auto rf = comp(filter(odd), take(3))(last_rf);

  auto s = rf(int{}, 41);
  s = state_rewrap(s, 13);
  EXPECT_EQ(state_unwrap_all(s), 13);
  s = rf(rf(rf(s, 1), 2), 3);
  EXPECT_EQ(state_unwrap_all(s), 3);
  EXPECT_TRUE(state_is_reduced(s));
}

TEST(state_traits, rewrap_type_erased)
{
  auto rf = transducer<int>{identity} (last_rf);

  auto s = rf(int{}, 41);
  s = state_rewrap(s, 13);
  EXPECT_EQ(state_unwrap_all(s), 13);
}

TEST(state_traits, rewrap_moar_complex)
{
  auto odd = [] (std::size_t x) { return x % 2; };
  auto rf = transducer<meta::pack<>, std::size_t>{
    comp(enumerate, filter(odd), take(10))} (last_rf);

  auto s = rf(std::size_t{});
  s = rf(s);
  s = state_rewrap(s, std::size_t{13});
  EXPECT_EQ(state_unwrap_all(s), 13);
  s = rf(s);
  EXPECT_EQ(state_unwrap_all(s), 13);
  s = rf(s);
  EXPECT_EQ(state_unwrap_all(s), 3);
}

} // namespace xform
} // namespace atria
