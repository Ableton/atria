// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/complement.hpp>
#include <random>

namespace atria {
namespace xform {

namespace detail {

struct default_generator
{
  std::default_random_engine engine = std::default_random_engine{};
  std::uniform_real_distribution<> distribution = std::uniform_real_distribution<>{};

  auto operator() ()
    -> ABL_DECLTYPE_RETURN(distribution(engine))
};

template <typename ProbabilityT, typename GeneratorT>
struct random_sampler
{
  ProbabilityT probability;
  GeneratorT generator;

  template <typename Ts>
  bool operator() (Ts&&...)
  {
    return generator() <= probability;
  }
};

} // namespace detail

/*!
 * Similar to clojure.core/random-sample$1
 */
template <typename ProbabilityT, typename GeneratorT = detail::default_generator>
auto random_sample(ProbabilityT prob, GeneratorT generator = GeneratorT{})
  -> ABL_DECLTYPE_RETURN(
    filter(detail::random_sampler<ProbabilityT, GeneratorT> {
        std::move(prob),
        std::move(generator)
    }))

} // namespace xform
} // namespace atria
