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
