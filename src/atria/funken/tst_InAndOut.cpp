// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/Commit.hpp>
#include <atria/funken/Inout.hpp>
#include <atria/funken/In.hpp>
#include <atria/funken/Out.hpp>
#include <atria/funken/State.hpp>
#include <atria/funken/Watch.hpp>
#include <atria/testing/Spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace funken {

TEST(Values, TypesConcepts)
{
  meta::check<In_value<In<int>>>();
  meta::check<Out_value<Out<int>>>();
  meta::check<Inout_value<Inout<int>>>();
}

TEST(Values, FactoriesConcepts)
{
  meta::check<In_value<decltype(in(state(0)))>>();
  meta::check<Out_value<decltype(out(state(0)))>>();
  meta::check<Inout_value<decltype(inout(state(0)))>>();
}

TEST(In, ConstructionAndAssignmentFromTemporary)
{
  In<int> in1;
  in1 = in(state(0));
  In<int> in2 { in(state(0)) };
}

TEST(Out, ConstructionAndAssignmentFromTemporary)
{
  Out<int> out1;
  out1 = out(state(0));
  Out<int> out2 { out(state(0)) };
}

TEST(Inout, ConstructionAndAssignmentFromTemporary)
{
  Inout<int> inout1;
  inout1 = inout(state(0));
  Inout<int> inout2 { inout(state(0)) };
}

TEST(Values, RelaxingRequirementsWorks)
{
  In<int> in1 = in(state(0));
  In<int> in2 = in(inout(state(0)));
  Out<int> out1 = out(state(0));
  Out<int> out2 = out(inout(state(0)));
}

TEST(In, WatchingAndGetting)
{
  auto st = state(0);
  auto i = in(st);
  auto s = testing::spy();

  watch(i, s);
  st.set(42);
  commit(st);

  EXPECT_EQ(42, i.get());
  EXPECT_EQ(1, s.count());
}

TEST(Inout, WatchingAndSettingAndGetting)
{
  auto st = state(0);
  auto io = inout(st);
  auto s = testing::spy();

  watch(io, s);
  io.set(42);
  commit(st);

  EXPECT_EQ(42, io.get());
  EXPECT_EQ(1, s.count());
}

TEST(Out, Setting)
{
  auto st = state(0);
  auto o = out(st);

  o.set(42);
  commit(st);
  EXPECT_EQ(42, st.get());
}

TEST(Out, SettingErased)
{
  auto st = state(0);
  auto o = Out<int>{ out(st) };

  o.set(42);
  commit(st);
  EXPECT_EQ(42, st.get());
}

TEST(Values, ScopedWatching)
{
  auto st = state(0);
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

TEST(Inout, StrentheningRequirementsDoesntWork)
{
  // In<int> in1 = in(out(state(0)));
  // In<int> in2 = in(out(inout(state(0))));
  // Out<int> out1 = out(in(state(0)));
  // Out<int> out2 = out(in(inout(state(0))));
}

} // namespace funken
} // namespace atria
