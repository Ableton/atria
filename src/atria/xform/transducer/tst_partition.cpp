// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/partition.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(partition, concept)
{
  meta::check<Transducer_spec(decltype(partition(2)),
                              int,
                              std::vector<int>)>();
}

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

TEST(into, partition_does_not_copy_step_function)
{
  auto step = testing::copy_spy<first_rf_t>{};

  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  reduce(partition(2u)(step), 0, v);
  EXPECT_EQ(step.copied.count(), 2);
}

TEST(reduce, partition_moves_the_state_through)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto spy = reduce(partition(2u)(first_rf), testing::copy_spy<>{}, v);
  EXPECT_EQ(spy.copied.count(), 0);
}

TEST(reduce, reduce_nested_deals_with_empty_sequence_properly)
{
  auto v = std::vector<std::vector<int> > {{{}, {1, 2, 3}, {}}};
  auto res = into(
    std::vector<std::vector<int>>{},
    comp(cat, transducer<int, std::vector<int>>{partition(2u)}),
    v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {{1, 2}, {3}}));
}

} // namespace xform
} // namespace atria
