// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <numeric>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty_accumulate(ReducingFnT&& step,
                                        StateT&& state,
                                        InputRangeT&& range)
  -> estd::decay_t<StateT>
{
  return std::accumulate(
    std::begin(range),
    std::end(range),
    std::forward<StateT>(state),
    std::forward<ReducingFnT>(step));
}

} // namespace detail
} // namespace xform
} // namespace atria
