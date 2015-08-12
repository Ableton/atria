// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/testing/benchmark.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transduce.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <cxxopts.hpp>
ABL_RESTORE_WARNINGS

#include <vector>
#include <iostream>
#include <iomanip>
#include <typeinfo>

namespace atria {
namespace testing {

void unoptimize(const void*)
{
}

namespace detail {

benchmark_suite_base::~benchmark_suite_base()
{
  std::cout << std::endl << name_ << " --" << std::endl;
  if (!results_.empty()) {
    auto best_time  = std::get<0>(*results_.begin());
    auto name_width = xform::transduce(
      xform::map([] (std::tuple<double, std::string> item) {
        return std::get<1>(item).size();
      }),
      [] (std::size_t acc, std::size_t next) {
        return std::max(acc, next);
      },
      std::size_t{},
      results_);

    for (auto& result : results_) {
      auto& time = std::get<0>(result);
      auto& name = std::get<1>(result);
      std::cout << "    "
                << name << std::string(name_width - name.size(), ' ') << " | "
                << std::setw(10) << time << " | "
                << std::setw(10) << time / best_time
                << std::endl;
    }
  } else {
    std::cout << "    no benchmarks" << std::endl;
  }
}

} // namespace detail

namespace {

auto optv(bool& x)
  -> ABL_DECLTYPE_RETURN(
    cxxopts::value<bool>(x))

template <typename T>
auto optv(T& x)
  -> ABL_DECLTYPE_RETURN(
    cxxopts::value<T>(x)
    ->default_value(std::to_string(x)))

} // namespace

benchmark_runner::benchmark_runner(int argc, char const*const* argv,
                                   benchmark_settings settings)
  : settings_(std::move(settings))
{
  auto opts = cxxopts::Options{ argv[0], "" };
  auto help = bool{};

  opts.add_options()
    ("h,help", "print help message",
     optv(help))
    ("v,verbose", "show more output",
     optv(settings_.verbose))
    ("i,iterations", "number of times to run the benchmark per measurement",
     optv(settings_.iterations), "NUM")
    ("m,measurements", "number of times to measure each benchmark",
     optv(settings_.measurements), "NUM")
    ("s,size", "amount of data to pass to each benchmark",
     optv(settings_.size), "NUM")
    ;

  auto argv_ = const_cast<char**>(argv);
  opts.parse(argc, argv_);

  if (help) {
    throw benchmark_runner_error{ opts.help() };
  }
}

} // namespace testing
} // namespace atria
