// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into_vector.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/partition_by.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(partition_by, partition_by)
{
  auto v = std::vector<int> { 1, 1, 2, 2, 2, 3 };

  auto res = into_vector(partition_by(identity), v);
  EXPECT_EQ(res, (decltype(res) {
        {1, 1}, {2, 2, 2}, {3}
      }));
}

namespace {
int free_mod2(int x) { return x % 2; }
} // anonymous

TEST(partition_by, invoke)
{
  auto v = std::vector<int> { 1, 1, 2, 4, 2, 3 };

  auto res = into_vector(partition_by(free_mod2), v);
  EXPECT_EQ(res, (decltype(res) {
        {1, 1}, {2, 4, 2}, {3}
      }));
}

TEST(partition_by, partition_by_does_not_copy_step_function)
{
  auto step = testing::copy_spy<first_rf_t>{};

  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  reduce(partition_by(identity)(step), 0, v);
  EXPECT_EQ(step.copied.count(), 2);
}

TEST(partition_by, partition_by_moves_the_state_through)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto spy = reduce(partition_by(identity)(first_rf), testing::copy_spy<>{}, v);
  EXPECT_EQ(spy.copied.count(), 0);
}

TEST(partition_by, reduce_nested_deals_with_empty_sequence_properly)
{
  auto v = std::vector<std::vector<int> > {{{}, {1, 1, 2}, {}}};
  auto part = transducer<int, std::vector<int> > { partition_by(identity) };
  auto res = into_vector(comp(cat, part), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {{1, 1}, {2}}));
}

} // namespace xform
} // namespace atria
