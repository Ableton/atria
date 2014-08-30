// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/funken/Commit.hpp>
#include <ableton/funken/Concepts.hpp>
#include <ableton/funken/Sensor.hpp>
#include <ableton/funken/Watch.hpp>
#include <ableton/testing/Spies.hpp>
#include <gtest/gtest.h>

namespace ableton {
namespace funken {

struct Counter
{
  std::size_t count = 0;
  std::size_t operator() ()
  {
    return count++;
  }
};

TEST(Sensor, Concepts)
{
  EXPECT_TRUE(estd::check<In_value<Sensor<Counter>>>());
  EXPECT_TRUE(estd::check<Out_value<Sensor<Counter>>>());
  EXPECT_TRUE(estd::check<Root_value<Sensor<Counter>>>());
}

TEST(Sensor, Basic)
{
  auto x = sensor([] { return 42; });
  EXPECT_EQ(42, x.get());
  commit(x);
  EXPECT_EQ(42, x.get());
}

TEST(Sensor, LooksUpOnlyOnCommit)
{
  auto x = sensor(Counter{});
  EXPECT_EQ(0, x.get());
  EXPECT_EQ(0, x.get());
  commit(x);
  EXPECT_EQ(1, x.get());
  EXPECT_EQ(1, x.get());
  commit(x);
  EXPECT_EQ(2, x.get());
}

TEST(Sensor, Watching)
{
  auto expectedOld = 0;
  auto expectedCurr = 1;
  auto x = sensor(Counter{});
  auto s = testing::spy([&](std::size_t old, std::size_t curr) {
      EXPECT_EQ(expectedOld, old);
      EXPECT_EQ(expectedCurr, curr);
    });
  watch(x, s);
  EXPECT_EQ(0, s.count());
  commit(x);
  EXPECT_EQ(1, s.count());
  ++expectedCurr, ++expectedOld;
  commit(x);
  EXPECT_EQ(2, s.count());
}

} // namespace funken
} // namespace ableton
