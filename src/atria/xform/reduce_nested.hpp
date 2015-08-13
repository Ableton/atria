// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/skip.hpp>
#include <atria/xform/detail/reduce_nested_non_empty.hpp>
#include <atria/xform/detail/is_non_empty.hpp>

namespace atria {
namespace xform {
namespace detail {

constexpr struct
{
  template <typename StateT,
            typename ReducingFnT,
            typename ...InputRangeTs>
  constexpr auto operator()(StateT&& state,
                            ReducingFnT&& step,
                            InputRangeTs&& ...ranges) const
    -> ABL_DECLTYPE_RETURN(
      reduce_nested_non_empty(
        std::forward<ReducingFnT>(step),
        std::forward<StateT>(state),
        std::forward<InputRangeTs>(ranges)...))

} reduce_nested_non_empty_flipped {};

} // namespace detail

//!
// Similar to @a reduce, but does not unwrap `reduced` values.  This is
// useful when calling reduce recursively inside a transducer.
// @see take
//
template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce_nested(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> ABL_DECLTYPE_RETURN(
    detail::is_non_empty(ranges...)
      ? call(detail::reduce_nested_non_empty_flipped,
             std::forward<StateT>(state),
             std::forward<ReducingFnT>(step),
             std::forward<InputRangeTs>(ranges)...)
      : skip(std::forward<StateT>(state)))

} // namespace xform
} // namespace atria
