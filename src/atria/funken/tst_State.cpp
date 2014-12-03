// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/Concepts.hpp>
#include <atria/funken/Commit.hpp>
#include <atria/funken/State.hpp>
#include <atria/funken/Watch.hpp>
#include <atria/testing/Spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace funken {

struct NoDefaultCtr
{
  NoDefaultCtr() = delete;
  NoDefaultCtr(int) {}
  bool operator==(NoDefaultCtr) const { return true; }
  bool operator!=(NoDefaultCtr) const { return false; }
};

TEST(State, Concepts)
{
  EXPECT_TRUE(meta::check<In_value<State<int>>>());
  EXPECT_TRUE(meta::check<Out_value<State<int>>>());
  EXPECT_TRUE(meta::check<Root_value<State<int>>>());
}

TEST(State, HoldsAValue)
{
  {
    auto x = state(1);
    EXPECT_EQ(x.get(), 1);
  }
  {
    auto x = state("hello");
    EXPECT_EQ(x.get(), "hello");
  }
  {
    auto x = State<int> {};
    EXPECT_EQ(x.get(), 0);
  }
  {
    auto x = state(NoDefaultCtr { 42 });
    EXPECT_EQ(x.get(), NoDefaultCtr { 42 });
  }
}

TEST(State, NewValuesArentVisible)
{
  auto x = state(42);
  x.set(13);
  EXPECT_EQ(x.get(), 42);
  x.set(16);
  EXPECT_EQ(x.get(), 42);
  x.set(19);
  EXPECT_EQ(x.get(), 42);
}

TEST(State, CommitMakesLatestValueVisible)
{
  auto x = state(42);
  x.set(13);
  commit(x);
  EXPECT_EQ(x.get(), 13);

  x.set(8);
  x.set(5);
  x.set(3);
  commit(x);
  EXPECT_EQ(x.get(), 3);
}

TEST(State, CommitIdempotence)
{
  auto x = state(42);
  x.set(13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
}

TEST(State, WatcheNotifiedOnCommit)
{
  auto x = state(42);
  auto s = testing::spy();
  watch(x, s);

  x.set(13);
  EXPECT_EQ(s.count(), 0);

  commit(x);
  EXPECT_EQ(s.count(), 1);
}

TEST(State, WatchesAlwaysViewConsistentState)
{
  auto x = state(42);
  auto y = state(35);
  auto sx = testing::spy([&](int old, int curr) {
      EXPECT_EQ(42, old);
      EXPECT_EQ(84, curr);
      EXPECT_EQ(x.get(), 84);
      EXPECT_EQ(y.get(), 70);
    });
  auto sy = testing::spy([&](int old, int curr) {
      EXPECT_EQ(35, old);
      EXPECT_EQ(70, curr);
      EXPECT_EQ(x.get(), 84);
      EXPECT_EQ(y.get(), 70);
    });

  watch(x, sx);
  watch(y, sy);

  x.set(84);
  y.set(70);
  EXPECT_EQ(sx.count(), 0);
  EXPECT_EQ(sy.count(), 0);

  commit(x, y);
  EXPECT_EQ(sx.count(), 1);
  EXPECT_EQ(sy.count(), 1);
}

TEST(State, CapsuleCarriesItsOwnWatchers)
{
  auto sig = std::shared_ptr<detail::StateUpDownSignal<int>>{};
  auto s = testing::spy();
  {
    auto st = state(42);
    sig = detail::Access::signal(st);
    watch(st, s);
    sig->pushDown(12);
    sig->sendDown();
    sig->notify();
    EXPECT_EQ(1, s.count());
  }
  sig->pushDown(7);
  sig->sendDown();
  sig->notify();
  EXPECT_EQ(1, s.count());
  EXPECT_TRUE(sig->observers().empty());
}

} // namespace funken
} // namespace atria
