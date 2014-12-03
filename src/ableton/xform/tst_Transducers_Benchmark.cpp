// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

//! @note Turn to one to check if our custom accumulate has any
//! performance cost or not.
//
// #define ABL_REDUCE_WITH_ACCUMULATE 1
// #define ABL_REDUCE_NON_VARIADIC 0

#include <ableton/build_system/Warnings.hpp>
#include <ableton/xform/Transducers.hpp>
#include <ableton/testing/Benchmark.hpp>
#include <ableton/testing/gtest.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
ABL_RESTORE_WARNINGS

namespace ableton {
namespace funken {

using namespace xform;

constexpr auto DATA_SIZE  = 1000;
constexpr auto ITERATIONS = 1000;

template <typename FnT>
void xformBenchmark(FnT&& fn)
{
  auto data = std::vector<int>(DATA_SIZE);
  boost::iota(data, 0);
  for (std::size_t n = 0; n < ITERATIONS; ++n)
    testing::unoptimize(fn(data));
}

TEST(Transduce_Benchmark, FilterMapCopy_BoostRange)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      using namespace boost::adaptors;
      auto result = std::vector<int>{};
      boost::copy(
        data
        | filtered([](int x) { return x % 2 == 0; })
        | transformed([](int x) { return x * 2; }),
        std::back_inserter(result));
      return result;
    });
}

TEST(Transduce_Benchmark, FilterMapCopy_Stl)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      std::vector<int> result;
      std::remove_copy_if(
        data.begin(), data.end(),
        std::back_inserter(result),
        [](int x) { return x % 2 == 0; });
      std::transform(
        result.begin(), result.end(), result.begin(),
        [](int x) { return x * 2; });
      return result;
    });
}

TEST(Transduce_Benchmark, FilterMapCopy_Transduce)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      return into(
        std::vector<int>{},
        comp(filter([](int x) { return x % 2 == 0; }),
             map([](int x) { return x * 2; })),
        data);
    });
}

TEST(Transduce_Benchmark, FilterMapReduce_BoostRange)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      using namespace boost::adaptors;
      return boost::accumulate(
        data
        | filtered([](int x) { return x % 2 == 0; })
        | transformed([](int x) { return x * 2; }),
        0,
        std::plus<int>{});
    });
}

TEST(Transduce_Benchmark, FilterMapReduce_Stl)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      std::vector<int> result;
      std::remove_copy_if(
        data.begin(), data.end(),
        std::back_inserter(result),
        [](int x) { return x % 2 == 0; });
      std::transform(
        result.begin(), result.end(), result.begin(),
        [](int x) { return x * 2; });
      return std::accumulate(
        result.begin(),
        result.end(),
        0,
        std::plus<int>{});
    });
}

TEST(Transduce_Benchmark, FilterMapReduce_Accumulate)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      return std::accumulate(
        data.begin(),
        data.end(),
        0,
        [](int state, int input) {
          if (input % 2 == 0)
          {
            return state + input * 2;
          }
          return state;
        });
    });
}

TEST(Transduce_Benchmark, FilterMapReduce_Transduce)
{
  xformBenchmark(
    [](const std::vector<int>& data)
    {
      return transduce(
        comp(filter([](int x) { return x % 2 == 0; }),
             map([](int x) { return x * 2; })),
        std::plus<int>{},
        0,
        data);
    });
}

} // namespace funken
} // namespace ableton
