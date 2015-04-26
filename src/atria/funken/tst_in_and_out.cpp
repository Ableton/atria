// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

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
  meta::check<In_value<input<int>>>();
  meta::check<Out_value<output<int>>>();
  meta::check<Inout_value<inoutput<int>>>();
}

TEST(values, factories_concepts)
{
  meta::check<In_value<decltype(in(make_state(0)))>>();
  meta::check<Out_value<decltype(out(make_state(0)))>>();
  meta::check<Inout_value<decltype(inout(make_state(0)))>>();
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
