// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/concepts.hpp>
#include <atria/funken/commit.hpp>
#include <atria/funken/state.hpp>
#include <atria/funken/watch.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace funken {

struct no_default_ctr
{
  no_default_ctr() = delete;
  no_default_ctr(int) {}
  bool operator==(no_default_ctr) const { return true; }
  bool operator!=(no_default_ctr) const { return false; }
};

TEST(state, Concepts)
{
  EXPECT_TRUE(meta::check<In_value_spec(state<int>)>());
  EXPECT_TRUE(meta::check<Out_value_spec(state<int>)>());
  EXPECT_TRUE(meta::check<Root_value_spec(state<int>)>());
}

TEST(state, holds_avalue)
{
  {
    auto x = make_state(1);
    EXPECT_EQ(x.get(), 1);
  }
  {
    auto x = make_state("hello");
    EXPECT_EQ(x.get(), "hello");
  }
  {
    auto x = state<int> {};
    EXPECT_EQ(x.get(), 0);
  }
  {
    auto x = make_state(no_default_ctr { 42 });
    EXPECT_EQ(x.get(), no_default_ctr { 42 });
  }
}

TEST(state, new_values_arent_visible)
{
  auto x = make_state(42);
  x.set(13);
  EXPECT_EQ(x.get(), 42);
  x.set(16);
  EXPECT_EQ(x.get(), 42);
  x.set(19);
  EXPECT_EQ(x.get(), 42);
}

TEST(state, commit_makes_latest_value_visible)
{
  auto x = make_state(42);
  x.set(13);
  commit(x);
  EXPECT_EQ(x.get(), 13);

  x.set(8);
  x.set(5);
  x.set(3);
  commit(x);
  EXPECT_EQ(x.get(), 3);
}

TEST(state, commit_idempotence)
{
  auto x = make_state(42);
  x.set(13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
  commit(x);
  EXPECT_EQ(x.get(), 13);
}

TEST(state, watche_notified_on_commit)
{
  auto x = make_state(42);
  auto s = testing::spy();
  watch(x, s);

  x.set(13);
  EXPECT_EQ(s.count(), 0);

  commit(x);
  EXPECT_EQ(s.count(), 1);
}

TEST(state, watches_always_view_consistent_state)
{
  auto x = make_state(42);
  auto y = make_state(35);
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

TEST(state, capsule_carries_its_own_watchers)
{
  auto sig = std::shared_ptr<detail::state_up_down_signal<int>>{};
  auto s = testing::spy();
  {
    auto st = make_state(42);
    sig = detail::access::signal(st);
    watch(st, s);
    sig->push_down(12);
    sig->send_down();
    sig->notify();
    EXPECT_EQ(1, s.count());
  }
  sig->push_down(7);
  sig->send_down();
  sig->notify();
  EXPECT_EQ(1, s.count());
  EXPECT_TRUE(sig->observers().empty());
}

} // namespace funken
} // namespace atria
