// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <iterator>

#include <atria/xform/config.hpp>
#include <atria/xform/detail/reduce_nested_non_empty_variadic.hpp>
#include <atria/xform/detail/reduce_nested_non_empty_nullary.hpp>

#if   ABL_REDUCE_TAIL_RECURSIVE
#  include <atria/xform/detail/reduce_nested_non_empty_tail_recursive.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_tail_recursive

#elif ABL_REDUCE_WITH_ACCUMULATE
#  include <atria/xform/detail/reduce_nested_non_empty_tail_accumulate.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_accumulate

#elif ABL_REDUCE_ALWAYS_VARIADIC
#  include <atria/xform/detail/reduce_nested_non_empty_variadic.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_variadic

#else
#  include <atria/xform/detail/reduce_nested_non_empty_non_variadic.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_non_variadic
#endif

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_nullary(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state)))

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state,
                             InputRangeT&& range)
  -> ABL_DECLTYPE_RETURN(
    ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeT>(range)))

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT,
          typename ...InputRangeTs>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state,
                             InputRangeT&& range,
                             InputRangeTs&& ...ranges)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_variadic(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeT>(range),
      std::forward<InputRangeTs>(ranges)...))

} // namespace detail
} // namespace xform
} // namespace atria
