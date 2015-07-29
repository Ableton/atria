// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/estd/type_traits.hpp>

ABL_DISABLE_WARNINGS
#include <boost/range/irange.hpp>
#include <boost/range/algorithm/for_each.hpp>
ABL_RESTORE_WARNINGS

#include <chrono>
#include <set>
#include <string>
#include <utility>
#include <tuple>
#include <iostream>
#include <functional>

namespace atria {
namespace testing {

/*!
 * Utility to prevent calls to code the could be inlineable by the
 * compiler being removed completely if the compiler can find this is
 * a no-op.  Just make sure the code returns something that is derived
 * from the work you are interested in benchmarking and passed to this
 * function.
 */
void unoptimize(const void*);

template <typename T>
void unoptimize(const T& x)
{
  unoptimize(reinterpret_cast<const void*>(&x));
}

/*!
 * In the spirit of Python's `timeit()`, takes a nullary function and
 * evaluates it, calculating how long it takes to execute.
 */
template <typename FnT>
auto timeit(FnT&& fn) ->
  std::chrono::duration<double, std::milli>
{
  auto t0 = std::chrono::steady_clock::now();

  std::forward<FnT>(fn)();

  auto t1 = std::chrono::steady_clock::now();
  return std::chrono::duration<double, std::milli>{t1 - t0};
}

/*!
 * Settings to configure a benchmark run.
 */
struct benchmark_settings
{
  //! How many times the benchmark is run per measurement.  This is
  //! needed because some operations might be too fast to be
  //! measurable at all.
  unsigned    iterations   = 100;

  //! Number of measurements or attempts to make per benchmark.  The
  //! minimum time measured be reported.
  unsigned    measurements = 100;

  //! Amount of data to use in the benchmark.  This is to be
  //! interpreted by the benchmark initialization code.
  std::size_t size         = 100;
};

namespace detail {

class benchmark_suite_base
{
public:
  ~benchmark_suite_base();
  benchmark_suite_base(const benchmark_suite_base&) = default;
  benchmark_suite_base(std::string name, benchmark_settings settings)
    : name_(std::move(name))
    , settings_(std::move(settings))
  {}

protected:
  const benchmark_settings& settings() { return settings_; }

  template <typename TestFnT>
  void run(std::string name, TestFnT test_fn)
  {
    auto minimum   = [] (double x, double y) { return std::min(x, y); };
    auto iteration = [&] (unsigned) { unoptimize(test_fn()); };
    auto measure   = [&] (unsigned) {
      return timeit([&] {
        boost::for_each(boost::irange(0u, settings_.iterations), iteration);
      }).count();
    };

    results_.insert(
      std::make_tuple(
        xform::transduce(
          xform::map(measure),
          minimum,
          std::numeric_limits<double>::max(),
          boost::irange(0u, settings_.measurements)),
        std::move(name)));
  }

private:
  std::string name_;
  benchmark_settings settings_;
  std::set<std::tuple<double, std::string> > results_;
};

} // namespace detail

/*!
 * A suite of benchmarks. It runs all benchmarks defined with the call
 * `()` operator and prints the results to the command line on
 * destruction.
 *
 * @see benchmark_runner for more details on how to use it.
 */
template <typename InitFnT=void>
class benchmark_suite : detail::benchmark_suite_base
{
public:
  benchmark_suite(std::string name, InitFnT init_fn,
                  benchmark_settings settings)
    : detail::benchmark_suite_base(std::move(name), std::move(settings))
    , init_fn_(std::move(init_fn))
  {}

  template <typename TestT>
  benchmark_suite& operator() (std::string name, TestT test)
  {
    const auto data = init_fn_(settings());
    run(std::move(name), std::bind(test, data));
    return *this;
  }

private:
  InitFnT init_fn_;
};

template <>
class benchmark_suite<void> : detail::benchmark_suite_base
{
public:
  using detail::benchmark_suite_base::benchmark_suite_base;

  template <typename TestT>
  benchmark_suite& operator() (std::string name, TestT&& test)
  {
    run(std::move(name), std::forward<TestT>(test));
    return *this;
  }
};

/*!
 * Error thrown by the `benchmark_runner` when it should not execute.
 * @see benchmark_runner
 */
struct benchmark_runner_error : std::runtime_error
{
  using std::runtime_error::runtime_error;
};

/*!
 * A class to run multiple suites of benchmarks.
 *
 * The runs can be configured by passing the command line arguments and
 * default settings to the constructor.
 *
 * The @a suite method can be used to create benchmark suites.  If an
 * *init function* is passed, benchmarks are passed data constructed
 * with it. Otherwise they should expect no arguments.  Benchmark
 * functions should return a value that depends on the computation
 * under test, to prevent the functions to be optimized away by the
 * compiler. An example is worth a thousand words:
 *
 * @code{.cpp}
 * void benchmarks(benchmark_runner runner)
 * {
 *   // Compare summing values with different methods.  Example of
 *   // benchmarks without initialization data.
 *   runner.suite("summing values")
 *     ("operator+", [] { return 1 + 2; })
 *     ("std::plus", [] { return std::plus<int>{}(1, 2); })
 *   ;
 *
 *   // Compare summing vectors with different methods.  The time it
 *   // takes to prepare the input data is not counted.  Note how the
 *   // init function takes the configured data size into account, so
 *   // the user can try different runs with different input sizes.
 *   runner.suite("summing vectors", [](benchmark_settings conf) {
 *       auto data = std::vector<int>(conf.size);
 *       std::itoa(data.begin(), data.end(), 1);
 *       return data;
 *     })
 *     ("std::accumulate", [] (const std::vector<int>& data) {
 *       return std::accumulate(data.begin(), data.end(), std::plus<int>{});
 *     })
 *     ("range for loop",  [] (const std::vector<int>& data) {
 *       int total;
 *       for (auto n : data) total += n;
 *       return total;
 *     })
 *   ;
 * }
 * @endcode
 */
class benchmark_runner
{
public:
  benchmark_runner(int argc, char const*const* argv,
                   benchmark_settings settings = {});

  template <typename InitFnT>
  auto suite(std::string name, InitFnT&& init_fn)
    -> benchmark_suite<estd::decay_t<InitFnT> >
  {
    return benchmark_suite<estd::decay_t<InitFnT> > {
      std::move(name),
      std::forward<InitFnT>(init_fn),
      settings_
    };
  }

  auto suite(std::string name) -> benchmark_suite<>
  {
    return benchmark_suite<> {
      std::move(name),
      settings_
    };
  }

private:
  benchmark_settings settings_;
};

/*!
 * Creates a `benchmark_runner` and passes it to @a fn, returning a
 * zero (success) code. If there is an error, prints it to the command
 * line and returns a non-zero (failure) value.
 */
template <typename FnT>
int benchmark_main(int argc, char const*const* argv, FnT&& fn)
{
  try {
    std::forward<FnT>(fn)(benchmark_runner(argc, argv));
  } catch (const benchmark_runner_error& ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}

/*!
 * Utility macro to define a benchmark running program.
 */
#define ABL_BENCHMARK_MAIN(fn)                                  \
  int main(int argc, char const*const* argv)                    \
  {                                                             \
    return ::atria::testing::benchmark_main(argc, argv, fn);    \
  }                                                             \
  /**/

} // namespace testong
} // namespace atria
