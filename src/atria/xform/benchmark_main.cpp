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

/*!
 * Use this to add benchmarks for checking the performance of
 * `boost::range::type_erased`
 *
 * @note Setting this to 1 makes the program crash on GCC 5.2, for
 *       unknown reasons.
 */
#define ABL_BENCHMARK_XFORM_USE_BOOST_RANGE_ERASED 0

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/zip.hpp>
#include <atria/xform/transducer/unzip.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/transducer/iter.hpp>
#include <atria/xform/impure/into.hpp>
#include <atria/xform/impure/transducer/transducer.hpp>
#include <atria/xform/impure/transducer/take.hpp>
#include <atria/xform/detail/reduce_nested_non_empty_tail_recursive.hpp>
#include <atria/prelude/identity.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/benchmark.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#if ABL_BENCHMARK_XFORM_USE_BOOST_RANGE_ERASED
#include <boost/range/adaptor/type_erased.hpp>
#endif
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
ABL_RESTORE_WARNINGS

namespace atria {
namespace xform {

namespace {

std::size_t num_to_take(std::vector<unsigned> const& data)
{
  return data.size() >> 1;
};

void benchmarks(testing::benchmark_runner runner)
{
  auto make_benchmark_data = [](testing::benchmark_settings settings)
  {
    auto data = std::vector<unsigned>(settings.size);
    boost::iota(data, 0);
    return data;
  };

  auto get_benchmark_size = [](testing::benchmark_settings settings)
  {
    return settings.size;
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

#if ABL_BENCHMARK_XFORM_USE_BOOST_RANGE_ERASED
    ("boost::range, erased", [] (std::vector<unsigned> const& data)
    {
      using namespace boost::adaptors;
      auto result = std::vector<unsigned>{};
      boost::copy(
        data
        | filtered([](unsigned x) { return x % 2 == 0; })
        | transformed([](unsigned x) { return x * 2; })
        | type_erased<unsigned, boost::single_pass_traversal_tag>{},
        std::back_inserter(result));
      return result;
    })
#endif

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
    })

    ("atria::xform, erased, impure", [] (std::vector<unsigned> const& data)
    {
      impure::transducer<unsigned> xform = comp(
        filter([](unsigned x) { return x % 2 == 0; }),
        map([](unsigned x) { return x * 2u; }));
      return impure::into(
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

#if ABL_BENCHMARK_XFORM_USE_BOOST_RANGE_ERASED
    ("boost::range, erased", [] (std::vector<unsigned> const& data)
    {
      using namespace boost::adaptors;
      return boost::accumulate(
        data
        | filtered([](unsigned x) { return x % 2 == 0; })
        | transformed([](unsigned x) { return x * 2u; })
        | type_erased<unsigned, boost::single_pass_traversal_tag>{},
        0u,
        std::plus<unsigned>{});
    })
#endif

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

    ("atria::xform, iter", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        comp(iter(data),
             filter([](unsigned x) { return x % 2 == 0; }),
             map([](unsigned x) { return x * 2u; })),
        std::plus<unsigned>{},
        0u);
    })

    ("atria::xform, recursive", [] (std::vector<unsigned> const& data)
    {
      return state_complete(
        detail::reduce_nested_non_empty_tail_recursive(
          comp(filter([](unsigned x) { return x % 2 == 0; }),
               map([](unsigned x) { return x * 2u; }))(
                 std::plus<unsigned>{}),
          0u,
          data));
    })

    ("atria::xform, variadic", [] (std::vector<unsigned> const& data)
    {
      return state_complete(
        detail::reduce_nested_non_empty_variadic(
          comp(filter([](unsigned x) { return x % 2 == 0; }),
               map([](unsigned x) { return x * 2u; }))(
                 std::plus<unsigned>{}),
          0u,
          data));
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
    })

    ("atria::xform, erased, impure", [] (std::vector<unsigned> const& data)
    {
      impure::transducer<unsigned> xform = comp(
        filter([](unsigned x) { return x % 2 == 0; }),
        map([](unsigned x) { return x * 2u; }));
      return impure::transduce(
        xform,
        std::plus<unsigned>{},
        0u,
      data);
    });

  runner.suite("take sum", make_benchmark_data)

    ("accumulate", [] (std::vector<unsigned> const& data)
    {
      const auto n = static_cast<std::ptrdiff_t>(num_to_take(data));
      // take
      auto first = data.begin();
      auto last  = data.end();
      auto remaining = std::distance(first, last);
      std::advance(first, std::min(remaining, n));
      // sum
      return std::accumulate(
        first,
        last,
        0u,
        std::plus<unsigned>{});
    })

    ("loop", [] (std::vector<unsigned> const& data)
    {
      auto n = num_to_take(data);
      unsigned state = 0u;
      for (const auto& input : data) {
        if (n == 0) break;
        --n;
        state += input;
      }
      return state;
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        take(num_to_take(data)),
        std::plus<unsigned>{},
        0u,
        data);
    })

    ("atria::xform, recursive", [] (std::vector<unsigned> const& data)
    {
      return state_complete(
        detail::reduce_nested_non_empty_tail_recursive(
          take(num_to_take(data))(
            std::plus<unsigned>{}),
          0u,
          data));
    })

    ("atria::xform, impure", [] (std::vector<unsigned> const& data)
    {
      return impure::transduce(
        impure::take(num_to_take(data)),
        std::plus<unsigned>{},
        0u,
        data);
    });

  runner.suite("filter take sum", make_benchmark_data)

    ("loop", [] (std::vector<unsigned> const& data)
    {
      auto n = num_to_take(data);
      unsigned state = 0u;
      for (const auto& input : data) {
        if (input % 2 == 0) {
          if (n == 0) break;
          --n;
          state += input;
        }
      }
      return state;
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             take(num_to_take(data))),
        std::plus<unsigned>{},
        0u,
        data);
    })

    ("atria::xform, 2-filter", [] (std::vector<unsigned> const& data)
    {
      // This is to ensure that skip_states are flattened
      return transduce(
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             filter([](unsigned) { return true; }),
             take(num_to_take(data))),
        std::plus<unsigned>{},
        0u,
        data);
    })

    ("atria::xform, recursive", [] (std::vector<unsigned> const& data)
    {
      return state_complete(
        detail::reduce_nested_non_empty_tail_recursive(
          comp(filter([](unsigned x) { return x % 2 == 0; }),
               take(num_to_take(data)))(
                 std::plus<unsigned>{}),
          0u,
          data));
    })

    ("atria::xform, impure", [] (std::vector<unsigned> const& data)
    {
      return impure::transduce(
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             impure::take(num_to_take(data))),
        std::plus<unsigned>{},
        0u,
        data);
    });

  runner.suite("filter take into", make_benchmark_data)

    ("loop", [] (std::vector<unsigned> const& data)
    {
      auto n = num_to_take(data);
      std::vector<unsigned> state ;
      for (const auto& input : data) {
        if (input % 2 == 0) {
          if (n == 0) break;
          --n;
          state.push_back(input);
        }
      }
      return state;
    })

    ("atria::xform, impure", [] (std::vector<unsigned> const& data)
    {
      return impure::into(
        std::vector<unsigned>{},
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             impure::take(num_to_take(data))),
        data);
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return into(
        std::vector<unsigned>{},
        comp(filter([](unsigned x) { return x % 2 == 0; }),
             take(num_to_take(data))),
        data);
    });

  runner.suite("variadic sum", make_benchmark_data)

    ("loop", [] (std::vector<unsigned> const& data)
    {
      auto result = 0u;
      for (auto x = data.begin(), y = data.begin();
           x != data.end() && y != data.end();
           ++x, ++y)
      {
        result += *x + *y;
      }
      return result;
    })

    ("atria::xform", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        identity,
        [] (unsigned x, unsigned y, unsigned z) { return x + y + z; },
        0u,
        data,
        data);
    })

    ("atria::xform, iter", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        iter(data, data),
        [] (unsigned x, unsigned y, unsigned z) { return x + y + z; },
        0u);
    })

    ("atria::xform, zip unzip", [] (std::vector<unsigned> const& data)
    {
      return transduce(
        comp(zip, unzip),
        [] (unsigned x, unsigned y, unsigned z) { return x + y + z; },
        0u,
        data,
        data);
    });

  struct counter
  {
    std::size_t count = 0;
    std::size_t operator() () { return count++; }
  };

  runner.suite("generate", get_benchmark_size)

    ("stl, generate_n", [] (std::size_t size)
    {
      auto res = std::vector<std::size_t>{};
      res.reserve(size);
      std::generate_n(std::back_inserter(res), size, counter{});
      return res;
    })

    ("stl, itoa", [] (std::size_t size)
    {
      auto res = std::vector<std::size_t>(size);
      std::iota(std::begin(res), std::end(res), 0u);
      return res;
    })

    ("atria::xform, map", [] (std::size_t size)
    {
      auto res = std::vector<std::size_t>{};
      res.reserve(size);
      into(res, comp(map(counter{}), take(size)));
      return res;
    })

    ("atria::xform, enumerate", [] (std::size_t size)
    {
      auto res = std::vector<std::size_t>{};
      res.reserve(size);
      into(res, comp(enumerate, take(size)));
      return res;
    });

}

} // anonymous namespace
} // namespace xform
} // namespace atria

ABL_BENCHMARK_MAIN(::atria::xform::benchmarks);
