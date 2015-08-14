// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/detail/reduce_nested_non_empty.hpp>
#include <atria/xform/detail/is_non_empty.hpp>
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/reduce.  Unlike `std::accumulate`, this
 * reduces over a range (doesn't take to distinct iterators) and can
 * reduce over several ranges at the same time.  It also supports
 * early termination for transducers.
 */
template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  return detail::is_non_empty(ranges...)
    ? state_complete(
      detail::reduce_nested_non_empty(
        std::forward<ReducingFnT>(step),
        std::forward<StateT>(state),
        std::forward<InputRangeTs>(ranges)...))
    : std::forward<StateT>(state);
}

} // namespace xform
} // namespace atria
