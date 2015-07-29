// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

//! @note Turn to one to check if our custom accumulate has any
//! performance cost or not.

#define ABL_REDUCE_WITH_ACCUMULATE 0
#define ABL_REDUCE_ALWAYS_VARIADIC 0
#define ABL_REDUCE_TAIL_RECURSIVE 0

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/transducer.hpp>

#include <atria/testing/benchmark.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
ABL_RESTORE_WARNINGS

namespace atria {
namespace xform {

namespace {

void benchmarks(testing::benchmark_runner runner)
{
  auto make_benchmark_data = [](testing::benchmark_settings settings)
  {
    auto data = std::vector<unsigned>(settings.size);
    boost::iota(data, 0);
    return data;
  };

  runner.suite("filter map into", make_benchmark_data)

    ("boost::range", [] (std::vector<unsigned> const& data)
    {
      using namespace boost::adaptors;
      auto result = std::vector<unsigned>{};
      boost::copy(
        data
        | filtered([](unsigned x) { return x % 2 == 0; })
        | transformed([](unsigned x) { return x * 2; }),
        std::back_inserter(result));
      return result;
    })

    ("stl", [] (std::vector<unsigned> const& data)
    {
      std::vector<unsigned> result;
      std::remove_copy_if(
        data.begin(), data.end(),
        std::back_inserter(result),
        [](unsigned x) { return x % 2 == 0; });
      std::transform(
        result.begin(), result.end(), result.begin(),
        [](unsigned x) { return x * 2u; });
      return result;
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return into(
        std::vector<unsigned>{},
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             map([](unsigned x) { return x * 2; })),
        data);
    })

    ("atria::xform, erased", [] (std::vector<unsigned> const& data)
    {
      transducer<unsigned> xform = comp(
        filter([](unsigned x) { return x % 2 == 0; }),
        map([](unsigned x) { return x * 2u; }));
      return into(
        std::vector<unsigned>{},
        xform,
        data);
    });

  runner.suite("filter map sum", make_benchmark_data)

    ("boost::range", [] (std::vector<unsigned> const& data)
    {
      using namespace boost::adaptors;
      return boost::accumulate(
        data
        | filtered([](unsigned x) { return x % 2 == 0; })
        | transformed([](unsigned x) { return x * 2u; }),
        0u,
        std::plus<unsigned>{});
    })

    ("stl", [] (std::vector<unsigned> data)
    {
      std::remove_if(
        data.begin(), data.end(),
        [](unsigned x) { return x % 2 == 0; });
      std::transform(
        data.begin(), data.end(), data.begin(),
        [](unsigned x) { return x * 2u; });
      return std::accumulate(
        data.begin(),
        data.end(),
        0u,
        std::plus<unsigned>{});
    })

    ("accumulate", [] (std::vector<unsigned> const& data)
    {
      return std::accumulate(
        data.begin(),
        data.end(),
        0u,
        [](unsigned state, unsigned input) {
          if (input % 2 == 0)
            return state + input * 2u;
          return state;
        });
    })

    ("loop", [] (std::vector<unsigned> const& data)
    {
      unsigned state = 0u;
      for (const auto& input : data) {
        if (input % 2 == 0) {
          state += input * 2u;
        }
      }
      return state;
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             map([](unsigned x) { return x * 2u; })),
        std::plus<unsigned>{},
        0u,
        data);
    })

    ("atria::xform, erased", [] (std::vector<unsigned> const& data)
    {
      transducer<unsigned> xform = comp(
        filter([](unsigned x) { return x % 2 == 0; }),
        map([](unsigned x) { return x * 2u; }));
      return transduce(
        xform,
        std::plus<unsigned>{},
        0u,
      data);
    });
}

} // anonymous namespace
} // namespace xform
} // namespace atria

ABL_BENCHMARK_MAIN(::atria::xform::benchmarks);
