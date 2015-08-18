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
#include <atria/funken/inout.hpp>
#include <atria/funken/in.hpp>
#include <atria/funken/out.hpp>
#include <atria/funken/state.hpp>
#include <atria/funken/watch.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace funken {

TEST(values, types_concepts)
{
  meta::check<In_value_spec(input<int>)>();
  meta::check<Out_value_spec(output<int>)>();
  meta::check<Inout_value_spec(inoutput<int>)>();
}

TEST(values, factories_concepts)
{
  meta::check<In_value_spec(decltype(in(make_state(0))))>();
  meta::check<Out_value_spec(decltype(out(make_state(0))))>();
  meta::check<Inout_value_spec(decltype(inout(make_state(0))))>();
}

TEST(in, ConstructionAndAssignmentFromTemporary)
{
  input<int> in1;
  in1 = in(make_state(0));
  input<int> in2 { in(make_state(0)) };
}

TEST(out, construction_and_assignment_from_temporary)
{
  output<int> out1;
  out1 = out(make_state(0));
  output<int> out2 { out(make_state(0)) };
}

TEST(inout, construction_and_assignment_from_temporary)
{
  inoutput<int> inout1;
  inout1 = inout(make_state(0));
  inoutput<int> inout2 { inout(make_state(0)) };
}

TEST(values, relaxing_requirements_works)
{
  input<int> in1 = in(make_state(0));
  input<int> in2 = in(inout(make_state(0)));
  output<int> out1 = out(make_state(0));
  output<int> out2 = out(inout(make_state(0)));
}

TEST(in, watching_and_getting)
{
  auto st = make_state(0);
  auto i = in(st);
  auto s = testing::spy();

  watch(i, s);
  st.set(42);
  commit(st);

  EXPECT_EQ(42, i.get());
  EXPECT_EQ(1, s.count());
}

TEST(inout, watching_and_setting_and_getting)
{
  auto st = make_state(0);
  auto io = inout(st);
  auto s = testing::spy();

  watch(io, s);
  io.set(42);
  commit(st);

  EXPECT_EQ(42, io.get());
  EXPECT_EQ(1, s.count());
}

TEST(out, setting)
{
  auto st = make_state(0);
  auto o = out(st);

  o.set(42);
  commit(st);
  EXPECT_EQ(42, st.get());
}

TEST(out, setting_erased)
{
  auto st = make_state(0);
  auto o = output<int>{ out(st) };

  o.set(42);
  commit(st);
  EXPECT_EQ(42, st.get());
}

TEST(values, scoped_watching)
{
  auto st = make_state(0);
  auto s = testing::spy();

  {
    auto i = in(st);
    auto io = inout(st);
    watch(i, s);
    watch(io, s);

    st.set(42);
    commit(st);
    EXPECT_EQ(2, s.count());
  }

  st.set(52);
  commit(st);
  EXPECT_EQ(2, s.count());
}

TEST(inout, strenthening_requirements_doesnt_work)
{
  // input<int> in1 = in(out(make_state(0)));
  // input<int> in2 = in(out(inout(make_state(0))));
  // output<int> out1 = out(in(make_state(0)));
  // output<int> out2 = out(in(inout(make_state(0))));
}

} // namespace funken
} // namespace atria
