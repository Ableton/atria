// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <iterator>
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty_non_variadic(ReducingFnT&& step,
                                          StateT&& initial,
                                          InputRangeT&& range)
  -> estd::decay_t<decltype(step(initial, *std::begin(range)))>
{
  auto first = std::begin(range);
  auto last  = std::end(range);
  auto state = step(std::forward<StateT>(initial), *first);
  // This may be expressed more brief with a:
  //    while(++first != last)
  // but the for loop seems to make compilers generate better code.
  for (++first; !state_is_reduced(state) && first != last; ++first) {
    // `x = std::move(x)` is undefined behaviour, hence the two
    // steps approach to protect for when `step` just forwards
    // the state back.
    auto new_state = step(std::move(state), *first);
    state = std::move(new_state);
  }
  return state;
}

} // namespace detail
} // namespace xform
} // namespace atria
