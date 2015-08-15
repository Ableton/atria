// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/count.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

/*!
 * Generator transducer version of Python `range`
 */
template <typename StopT>
constexpr auto range(StopT&& stop)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(),
      take(std::forward<StopT>(stop))))

template <typename StartT, typename StopT>
constexpr auto range(StartT&& start, StopT&& stop)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(start),
      take(std::max(decltype(stop - start){},
                    stop - start))))

template <typename StartT, typename StopT, typename StepT>
constexpr auto range(StartT&& start, StopT&& stop, StepT&& step)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(start, step),
      take(std::max(decltype((stop - start) / step){},
                    (stop - start) / step))))

} // namespace xform
} // namespace atria
