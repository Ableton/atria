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
