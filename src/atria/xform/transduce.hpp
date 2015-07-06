// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/config.hpp>
#include <atria/xform/reduce.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/transduce
 */
template <typename XformT,
          typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto transduce(XformT&& xform, ReducerT&& reducer,
               StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  auto xformed = xform(std::forward<ReducerT>(reducer));
  return reduce(
    xformed,
    state,
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
