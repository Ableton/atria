// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#include <cstdint>
#include <limits>

struct deterministic_engine
{
  std::uint64_t count = 0;
  constexpr static std::uint64_t max() {
    return std::numeric_limits<std::uint64_t>::max(); }
  constexpr static std::uint64_t min() {
    return std::numeric_limits<std::uint64_t>::min(); }
  std::uint64_t operator() () { return count += max() / 6; }
};

#define ABL_XFORM_DEFAULT_RANDOM_ENGINE deterministic_engine

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/random_sample.hpp>
#include <atria/xform/transducer/range.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(random_sample, concept)
{
  meta::check<Transducer_spec(decltype(filter(std::less<int>{})),
                              meta::pack<int, int>)>();
}

TEST(random_sample, simple)
{
  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0.5)),
              std::plus<std::size_t>{}, std::size_t{}),
            100);


  EXPECT_EQ(transduce(
              comp(range(20), random_sample(1)),
              std::plus<std::size_t>{}, std::size_t{}),
            190);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0)),
              std::plus<std::size_t>{}, std::size_t{}),
            0);
}

TEST(random_sample, custom_generator)
{
  auto eng = deterministic_engine{};
  auto gen = [eng] () mutable { return double(eng()) * 2 / eng.max(); };

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0.5, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            36);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(1, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            100);

  EXPECT_EQ(transduce(
              comp(range(20), random_sample(0, gen)),
              std::plus<std::size_t>{}, std::size_t{}),
            0);
}

} // namespace xform
} // namespace atria
