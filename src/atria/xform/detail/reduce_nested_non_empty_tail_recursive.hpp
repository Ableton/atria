// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <iterator>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT,
          typename InputIterT>
auto reduce_nested_non_empty_tail_recursive_impl(ReducingFnT&& step,
                                                 StateT&& state,
                                                 InputIterT&& first,
                                                 InputIterT&& last)
  -> estd::decay_t<StateT>
{
  if (state_is_reduced(state) || first == last)
    return std::forward<StateT>(state);

  auto next_state = step(std::forward<StateT>(state), *first);
  return reduce_nested_non_empty_tail_recursive_impl(
    std::forward<ReducingFnT>(step),
    std::move(next_state),
    std::forward<InputIterT>(++first),
    std::forward<InputIterT>(last));
}

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty_tail_recursive(ReducingFnT&& step,
                                            StateT&& initial,
                                            InputRangeT&& range)
  -> estd::decay_t<decltype(step(initial, *std::begin(range)))>
{
  auto first = std::begin(range);
  auto last  = std::end(range);
  auto state = step(std::forward<StateT>(initial), *first);
  return reduce_nested_non_empty_tail_recursive_impl(
    std::forward<ReducingFnT>(step),
    std::move(state),
    ++first,
    last);
}

} // namespace detail
} // namespace xform
} // namespace atria
