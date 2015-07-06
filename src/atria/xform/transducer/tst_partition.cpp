// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/partition.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(into, partition)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5, 6}
      }));
}

TEST(into, partition_flushing)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5}
      }));
}

namespace {

struct copy_spy : first_rf_t
{
  std::function<void()> copied = []{};

  copy_spy() = default;
  copy_spy(copy_spy&&) = default;
  copy_spy& operator=(copy_spy&&) = default;

  copy_spy(const copy_spy& x)
    : first_rf_t(x)
    , copied(x.copied)
  {
    copied();
  }

  copy_spy& operator=(const copy_spy& x)
  {
    first_rf_t::operator=(x);
    copied = x.copied;
    copied();
    return *this;
  }
};

} // anonymous namespace

TEST(into, partition_does_not_copy_step_function)
{
  auto step = copy_spy{};
  auto spy = testing::spy_on(step.copied);

  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  reduce(partition(2u)(std::move(step)), 0, v);
  EXPECT_EQ(spy.count(), 1);
}

} // namespace xform
} // namespace atria
