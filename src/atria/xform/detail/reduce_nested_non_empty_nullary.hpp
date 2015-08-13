// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT>
auto reduce_nested_non_empty_nullary(ReducingFnT&& step,
                                     StateT&& initial)
  -> estd::decay_t<decltype(step(initial))>
{
   auto state = step(std::forward<StateT>(initial));
   while (!state_is_reduced(state)) {
    // `x = std::move(x)` is undefined behaviour, hence the two
    // steps approach to protect for when `step` just forwards
    // the state back.
    auto new_state = step(std::move(state));
    state = std::move(new_state);
  }
  return state;
}

} // namespace detail
} // namespace xform
} // namespace atria
