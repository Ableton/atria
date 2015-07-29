// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/testing/benchmark.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transduce.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
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

benchmark_runner::benchmark_runner(int argc, char const*const* argv,
                                   benchmark_settings settings)
  : settings_(std::move(settings))
{
#define ABL_BENCHMARK_OPTION_S_(name__, sname__, desc__)              \
  (#name__ "," #sname__,                                              \
   ::boost::program_options::value<decltype(settings_.name__)>(       \
     &settings_.name__)                                               \
   ->default_value(settings_.name__)                                  \
   ->value_name("<value>"),                                           \
   desc__)                                                            \
    /**/

  namespace po = boost::program_options;
  auto desc = po::options_description{};
  desc.add_options()
    ("help,h", "print help message")
    ABL_BENCHMARK_OPTION_S_(
      iterations, i, "number of times to run the benchmark per measurement")
    ABL_BENCHMARK_OPTION_S_(
      measurements, m, "number of times to measure each benchmark")
    ABL_BENCHMARK_OPTION_S_(
      size, s, "amount of data to pass to each benchmark")
    ;

  auto args = po::variables_map{};
  po::store(po::parse_command_line(argc, argv, desc), args);
  po::notify(args);

  if (args.count("help")) {
    throw benchmark_runner_error {
      boost::lexical_cast<std::string>(desc) };
  }

#undef ABL_BENCHMARK_OPTION_S_
}

} // namespace testing
} // namespace atria
