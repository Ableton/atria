// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/xform/reduce_finished.hpp>

#include <atria/estd/type_traits.hpp>
#include <atria/estd/utility.hpp>

#include <algorithm>
#include <numeric>
#include <tuple>

//!
// When defined to 1, std::accumulate will be used as an
// implementation for reduce() over one single collection.  In that
// case, halting reducers (e.g. take) might not work.
//
#ifndef ABL_REDUCE_WITH_ACCUMULATE
#define ABL_REDUCE_WITH_ACCUMULATE 0
#endif

//!
// When defined to 1, reduce will be defined separately for the
// non-variadic version.
//
#ifndef ABL_REDUCE_NON_VARIADIC
#define ABL_REDUCE_NON_VARIADIC 1
#endif

namespace atria {
namespace xform {

namespace detail {

template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_accumulate(ReducerT&& reducer, StateT&& state, InputRangeT&& range)
  -> estd::decay_t<StateT>
{
  return std::accumulate(
    std::begin(range),
    std::end(range),
    std::forward<StateT>(state),
    std::forward<ReducerT>(reducer));
}

template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_variadic(ReducerT&& reducer,
                                StateT&& state,
                                InputRangeT&& range)
  -> estd::decay_t<StateT>
{
  for (auto first = std::begin(range),
            last  = std::end(range);
       first != last;
       ++first)
  {
    state = reducer(std::move(state), *first);
  }

  return state;
}

template <typename ReducerT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputRangeTs>
auto reduce_nested_variadic_impl(ReducerT&& reducer,
                                 StateT&& state,
                                 estd::index_sequence<Indices...>,
                                 InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  for (auto firsts = std::make_tuple(std::begin(ranges)...),
            lasts  = std::make_tuple(std::end(ranges)...);
       std::min({ std::get<Indices>(firsts) !=
                  std::get<Indices>(lasts)... });
       meta::noop(++std::get<Indices>(firsts)...))
  {
    state = reducer(std::move(state),
                    *std::get<Indices>(firsts)...);
  }

  return state;
}

template <typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce_nested_variadic(ReducerT&& reducer, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  return detail::reduce_nested_variadic_impl(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    estd::make_index_sequence<sizeof...(InputRangeTs)> {},
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace detail


#if ABL_REDUCE_WITH_ACCUMULATE
#  define ABL_REDUCE_NESTED_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_accumulate
#elif ABL_REDUCE_NON_VARIADIC
#  define ABL_REDUCE_NESTED_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_variadic
#else
#  define ABL_REDUCE_NESTED_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_variadic
#endif

//!
// Similar to @a reduce, but does not unwrap `reduced` values.  This is
// useful when calling reduce recursively inside a transducer.
// @see take
//
template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested(ReducerT&& reducer, StateT&& state, InputRangeT&& range)
  -> decltype(ABL_REDUCE_NESTED_NON_VARIADIC_IMPL(
                std::forward<ReducerT>(reducer),
                std::forward<StateT>(state),
                std::forward<InputRangeT>(range)))
{
  return ABL_REDUCE_NESTED_NON_VARIADIC_IMPL(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    std::forward<InputRangeT>(range));
}

template <typename ReducerT,
          typename StateT,
          typename InputRangeT,
          typename ...InputRangeTs>
auto reduce_nested(ReducerT&& reducer, StateT&& state, InputRangeT&& range,
                   InputRangeTs&& ...ranges)
  -> decltype(detail::reduce_nested_variadic(
                std::forward<ReducerT>(reducer),
                std::forward<StateT>(state),
                std::forward<InputRangeT>(range),
                std::forward<InputRangeTs>(ranges)...))
{
  return detail::reduce_nested_variadic(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    std::forward<InputRangeT>(range),
    std::forward<InputRangeTs>(ranges)...);
}

//!
// Similar to clojure.core/reduce.  Unlike `std::accumulate`, this
// reduces over a range (doesn't take to distinct iterators) and can
// reduce over several ranges at the same time.  It also supports
// early termination for transducers.
//
template <typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducerT&& reducer, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  try {
    return reduce_nested(
      std::forward<ReducerT>(reducer),
      std::forward<StateT>(state),
      std::forward<InputRangeTs>(ranges)...);
  } catch (reduce_finished_exception<estd::decay_t<StateT>>& e) {
    return std::move(e.value);
  }
}

} // namespace xform
} // namespace atria
