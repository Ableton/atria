// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/complement.hpp>
#include <random>

#ifndef ABL_XFORM_DEFAULT_RANDOM_ENGINE
#define ABL_XFORM_DEFAULT_RANDOM_ENGINE ::std::default_random_engine
#endif

namespace atria {
namespace xform {

namespace detail {

struct default_generator
{
  using engine_t = ABL_XFORM_DEFAULT_RANDOM_ENGINE;
  using distribution_t =  std::uniform_real_distribution<>;

  engine_t engine = engine_t{};
  distribution_t distribution = distribution_t{};

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
