// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/detail/signals.hpp>
#include <atria/funken/detail/xform_signals.hpp>
#include <atria/funken/detail/root_signals.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>
#include <array>

namespace atria {
namespace funken {
namespace detail {

TEST(signal, instantiate_down_signal)
{
  make_xform_down_signal(identity);
}

TEST(signal, instantiate_state)
{
  make_state_signal(0);
}

TEST(signal, last_value_is_not_visible)
{
  auto x = make_state_signal(0);
  x->send_up(12);
  EXPECT_EQ(0, x->last());
  x->send_up(42);
  EXPECT_EQ(0, x->last());
}

TEST(signal, last_value_becomes_visible)
{
  auto x = make_state_signal(0);

  x->send_up(12);
  x->send_down();
  EXPECT_EQ(12, x->last());

  x->send_up(42);
  x->send_down();
  EXPECT_EQ(42, x->last());
}

TEST(signal, sending_down)
{
  auto x = make_state_signal(5);
  auto y = make_xform_down_signal(identity, x);
  EXPECT_EQ(5, y->last());

  x->send_up(12);
  x->send_down();
  EXPECT_EQ(12, y->last());

  x->send_up(42);
  x->send_down();
  EXPECT_EQ(42, y->last());
}

TEST(signal, notifies_new_and_previous_value_after_send_down)
{
  auto x = make_state_signal(5);
  auto s = testing::spy([](int last, int next) {
      EXPECT_EQ(5, last);
      EXPECT_EQ(42, next);
    });
  x->observe(s);

  x->send_up(42);
  EXPECT_EQ(0, s.count());

  x->notify();
  EXPECT_EQ(0, s.count());

  x->send_down();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(signal, lifetime_of_observer)
{
  auto x = make_state_signal(5);
  auto s = testing::spy();
  auto c = boost::signals2::connection{};
  {
    auto y = make_xform_down_signal(identity, x);
    c = y->observe(s);
    EXPECT_TRUE(c.connected());

    x->push_down(56);
    x->send_down();
    x->notify();
    EXPECT_EQ(1, s.count());
  }
  EXPECT_FALSE(c.connected());

  x->push_down(26);
  x->send_down();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(signal, notify_idempotence)
{
  auto x = make_state_signal(5);
  auto s = testing::spy();
  x->observe(s);

  x->send_up(42);
  EXPECT_EQ(0, s.count());

  x->notify();
  x->notify();
  x->notify();
  EXPECT_EQ(0, s.count());

  x->send_down();
  x->notify();
  x->notify();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(signal, observing_is_consistent)
{
  auto x = make_state_signal(5);
  auto y = make_xform_down_signal(identity, x);
  auto z = make_xform_down_signal(identity, x);
  auto w = make_xform_down_signal(identity, y);

  auto s = testing::spy([&] (int lastValue, int newValue) {
      EXPECT_EQ(5, lastValue);
      EXPECT_EQ(42, newValue);
      EXPECT_EQ(42, x->last());
      EXPECT_EQ(42, y->last());
      EXPECT_EQ(42, z->last());
      EXPECT_EQ(42, w->last());
    });

  x->observe(s);
  y->observe(s);
  z->observe(s);
  w->observe(s);

  x->send_up(42);
  x->send_down();
  EXPECT_EQ(0, s.count());

  x->notify();
  EXPECT_EQ(4, s.count());
}

TEST(signal, bidirectional_signal_sends_values_up)
{
  auto x = make_state_signal(5);
  auto y = make_xform_up_down_signal(identity, identity, x);

  y->send_up(42);
  EXPECT_EQ(5, x->last());
  EXPECT_EQ(5, y->last());

  x->send_down();
  EXPECT_EQ(42, x->last());
  EXPECT_EQ(42, y->last());
}

TEST(signal, bidirectional_mapping)
{
  auto inc = [](int x) { return ++x; };
  auto dec = [](int x) { return --x; };
  auto x = make_state_signal(5);
  auto y = make_xform_up_down_signal(map(inc), map(dec), x);

  EXPECT_EQ(5, x->last());
  EXPECT_EQ(6, y->last());

  y->send_up(42);
  x->send_down();
  EXPECT_EQ(41, x->last());
  EXPECT_EQ(42, y->last());

  x->send_up(42);
  x->send_down();
  EXPECT_EQ(42, x->last());
  EXPECT_EQ(43, y->last());
}

TEST(signal, bidirectiona_update_is_consistent)
{
  using arr = std::array<int, 2>;
  auto x = make_state_signal(arr {{ 5, 13 }});
  auto y = make_xform_up_down_signal(
    map([](const arr& a) { return a[0]; }),
    update([](arr a, int v) { a[0] = v; return a; }),
    x);
  auto z = make_xform_up_down_signal(
    map([](const arr& a) { return a[1]; }),
    update([](arr a, int v) { a[1] = v; return a; }),
    x);

  EXPECT_EQ((arr{{ 5, 13 }}), x->last());
  EXPECT_EQ(5, y->last());
  EXPECT_EQ(13, z->last());

  z->send_up(42);
  y->send_up(69);
  EXPECT_EQ((arr{{ 5, 13 }}), x->last());
  EXPECT_EQ(5, y->last());
  EXPECT_EQ(13, z->last());

  x->send_down();
  EXPECT_EQ((arr{{ 69, 42 }}), x->last());
  EXPECT_EQ(69, y->last());
  EXPECT_EQ(42, z->last());
}

TEST(signal, sensors_signals_reevaluate_on_send_down)
{
  int count = 0;
  auto x = make_sensor_signal([&count] { return count++; });
  EXPECT_EQ(0, x->last());
  x->send_down();
  EXPECT_EQ(1, x->last());
  x->send_down();
  EXPECT_EQ(2, x->last());
}

TEST(signal, one_signal_two_parents)
{
  int count = 0;
  auto x = make_sensor_signal([&count] { return count++; });
  auto y = make_state_signal(12);
  auto z = make_xform_down_signal(map([](int a, int b) { return a + b; }),
                               x, y);
  auto s = testing::spy([&](int _, int r) {
      EXPECT_EQ(x->last() + y->last(), r);
    });
  z->observe(s);
  EXPECT_EQ(12, z->last());

  // Commit first root individually
  x->send_down();
  EXPECT_EQ(13, z->last());
  EXPECT_EQ(0, s.count());
  x->notify();
  EXPECT_EQ(1, s.count());
  y->notify();
  EXPECT_EQ(1, s.count());

  // Commit second root individually
  y->push_down(3);
  y->send_down();
  EXPECT_EQ(4, z->last());
  y->notify();
  EXPECT_EQ(2, s.count());
  x->notify();
  EXPECT_EQ(2, s.count());

  // Commit both roots together
  x->send_down();
  y->push_down(69);
  y->send_down();
  x->notify();
  y->notify();
  EXPECT_EQ(71, z->last());
  EXPECT_EQ(3, s.count());
}

} // namespace detail
} // namespace funken
} // namespace atria
