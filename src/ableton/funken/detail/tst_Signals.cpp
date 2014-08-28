// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/funken/detail/Signals.hpp>
#include <ableton/funken/detail/XformSignals.hpp>
#include <ableton/funken/detail/RootSignals.hpp>
#include <ableton/testing/Spies.hpp>
#include <gtest/gtest.h>
#include <array>

namespace ableton {
namespace funken {
namespace detail {

TEST(Signal, InstantiateDownSignal)
{
  makeXformDownSignal(identity);
}

TEST(Signal, InstantiateState)
{
  makeStateSignal(0);
}

TEST(Signal, LastValueIsNotVisible)
{
  auto x = makeStateSignal(0);
  x->sendUp(12);
  EXPECT_EQ(0, x->last());
  x->sendUp(42);
  EXPECT_EQ(0, x->last());
}

TEST(Signal, LastValueBecomesVisible)
{
  auto x = makeStateSignal(0);

  x->sendUp(12);
  x->sendDown();
  EXPECT_EQ(12, x->last());

  x->sendUp(42);
  x->sendDown();
  EXPECT_EQ(42, x->last());
}

TEST(Signal, SendingDown)
{
  auto x = makeStateSignal(5);
  auto y = makeXformDownSignal(identity, x);
  EXPECT_EQ(5, y->last());

  x->sendUp(12);
  x->sendDown();
  EXPECT_EQ(12, y->last());

  x->sendUp(42);
  x->sendDown();
  EXPECT_EQ(42, y->last());
}

TEST(Signal, NotifiesNewAndPreviousValueAfterSendDown)
{
  auto x = makeStateSignal(5);
  auto s = testing::spy([](int last, int next) {
      EXPECT_EQ(5, last);
      EXPECT_EQ(42, next);
    });
  x->observe(s);

  x->sendUp(42);
  EXPECT_EQ(0, s.count());

  x->notify();
  EXPECT_EQ(0, s.count());

  x->sendDown();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(Signal, LifetimeOfObserver)
{
  auto x = makeStateSignal(5);
  auto s = testing::spy();
  auto c = boost::signals2::connection{};
  {
    auto y = makeXformDownSignal(identity, x);
    c = y->observe(s);
    EXPECT_TRUE(c.connected());

    x->pushDown(56);
    x->sendDown();
    x->notify();
    EXPECT_EQ(1, s.count());
  }
  EXPECT_FALSE(c.connected());

  x->pushDown(26);
  x->sendDown();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(Signal, NotifyIdempotence)
{
  auto x = makeStateSignal(5);
  auto s = testing::spy();
  x->observe(s);

  x->sendUp(42);
  EXPECT_EQ(0, s.count());

  x->notify();
  x->notify();
  x->notify();
  EXPECT_EQ(0, s.count());

  x->sendDown();
  x->notify();
  x->notify();
  x->notify();
  EXPECT_EQ(1, s.count());
}

TEST(Signal, ObservingIsConsistent)
{
  auto x = makeStateSignal(5);
  auto y = makeXformDownSignal(identity, x);
  auto z = makeXformDownSignal(identity, x);
  auto w = makeXformDownSignal(identity, y);

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

  x->sendUp(42);
  x->sendDown();
  EXPECT_EQ(0, s.count());

  x->notify();
  EXPECT_EQ(4, s.count());
}

TEST(Signal, BidirectionalSignalSendsValuesUp)
{
  auto x = makeStateSignal(5);
  auto y = makeXformUpDownSignal(identity, identity, x);

  y->sendUp(42);
  EXPECT_EQ(5, x->last());
  EXPECT_EQ(5, y->last());

  x->sendDown();
  EXPECT_EQ(42, x->last());
  EXPECT_EQ(42, y->last());
}

TEST(Signal, BidirectionalMapping)
{
  auto inc = [](int x) { return ++x; };
  auto dec = [](int x) { return --x; };
  auto x = makeStateSignal(5);
  auto y = makeXformUpDownSignal(map(inc), map(dec), x);

  EXPECT_EQ(5, x->last());
  EXPECT_EQ(6, y->last());

  y->sendUp(42);
  x->sendDown();
  EXPECT_EQ(41, x->last());
  EXPECT_EQ(42, y->last());

  x->sendUp(42);
  x->sendDown();
  EXPECT_EQ(42, x->last());
  EXPECT_EQ(43, y->last());
}

TEST(Signal, BidirectionaUpdateIsConsistent)
{
  using arr = std::array<int, 2>;
  auto x = makeStateSignal(arr {{ 5, 13 }});
  auto y = makeXformUpDownSignal(
    map([](const arr& a) { return a[0]; }),
    update([](arr a, int v) { a[0] = v; return a; }),
    x);
  auto z = makeXformUpDownSignal(
    map([](const arr& a) { return a[1]; }),
    update([](arr a, int v) { a[1] = v; return a; }),
    x);

  EXPECT_EQ((arr{{ 5, 13 }}), x->last());
  EXPECT_EQ(5, y->last());
  EXPECT_EQ(13, z->last());

  z->sendUp(42);
  y->sendUp(69);
  EXPECT_EQ((arr{{ 5, 13 }}), x->last());
  EXPECT_EQ(5, y->last());
  EXPECT_EQ(13, z->last());

  x->sendDown();
  EXPECT_EQ((arr{{ 69, 42 }}), x->last());
  EXPECT_EQ(69, y->last());
  EXPECT_EQ(42, z->last());
}

TEST(Signal, SensorsSignalsReevaluateOnSendDown)
{
  int count = 0;
  auto x = makeSensorSignal([&count] { return count++; });
  EXPECT_EQ(0, x->last());
  x->sendDown();
  EXPECT_EQ(1, x->last());
  x->sendDown();
  EXPECT_EQ(2, x->last());
}

TEST(Signal, OneSignalTwoParents)
{
  int count = 0;
  auto x = makeSensorSignal([&count] { return count++; });
  auto y = makeStateSignal(12);
  auto z = makeXformDownSignal(map([](int a, int b) { return a + b; }),
                               x, y);
  auto s = testing::spy([&](int _, int r) {
      EXPECT_EQ(x->last() + y->last(), r);
    });
  z->observe(s);
  EXPECT_EQ(12, z->last());

  // Commit first root individually
  x->sendDown();
  EXPECT_EQ(13, z->last());
  EXPECT_EQ(0, s.count());
  x->notify();
  EXPECT_EQ(1, s.count());
  y->notify();
  EXPECT_EQ(1, s.count());

  // Commit second root individually
  y->pushDown(3);
  y->sendDown();
  EXPECT_EQ(4, z->last());
  y->notify();
  EXPECT_EQ(2, s.count());
  x->notify();
  EXPECT_EQ(2, s.count());

  // Commit both roots together
  x->sendDown();
  y->pushDown(69);
  y->sendDown();
  x->notify();
  y->notify();
  EXPECT_EQ(71, z->last());
  EXPECT_EQ(3, s.count());
}

} // namespace detail
} // namespace funken
} // namespace ableton
