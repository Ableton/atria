//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include <atria/xform/concepts.hpp>
#include <atria/xform/into.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/partition.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/take.hpp>
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

TEST(partition, partition)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5, 6}
      }));
}

TEST(partition, partition_flushing)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5}
      }));
}

TEST(partition, partition_does_not_copy_step_function)
{
  auto step = testing::copy_spy<first_rf_t>{};

  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  reduce(partition(2u)(step), 0, v);
  EXPECT_EQ(step.copied.count(), 2);
}

TEST(partition, partition_moves_the_state_through)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto spy = reduce(partition(2u)(first_rf), testing::copy_spy<>{}, v);
  EXPECT_EQ(spy.copied.count(), 0);
}

TEST(partition, defining_early_termination_with_completion)
{
  auto v = std::vector<int> {{1, 2, 3, 4, 5}};
  auto res = into(
    std::vector<std::vector<int>>{},
    comp(take(3), partition(2u)),
    v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {{1, 2}, {3}}));
}

TEST(partition, reduce_nested_deals_with_empty_sequence_properly)
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
