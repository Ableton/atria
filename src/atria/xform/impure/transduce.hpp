// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/impure/reduce.hpp>

namespace atria {
namespace xform {
namespace impure {

template <typename XformT,
          typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto transduce(XformT&& xform, ReducingFnT&& step,
               StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  auto xformed = xform(std::forward<ReducingFnT>(step));
  return impure::reduce(
    xformed,
    state,
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace impure
} // namespace xform
} // namespace atria
