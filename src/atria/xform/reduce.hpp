// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/xform/state.hpp>

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
                                StateT&& initial,
                                InputRangeT&& range)
  -> estd::decay_t<decltype(reducer(initial, *std::begin(range)))>
{
  using result_t = estd::decay_t<decltype(reducer(initial, *std::begin(range)))>;

  auto first = std::begin(range);
  auto last  = std::end(range);
  if (first != last) {
    auto state = reducer(std::forward<StateT>(initial), *first);
    // This may be expressed more brief with a:
    //    while(++first != last)
    // but the for loop seems to make compilers generate better code.
    for (++first; !state_is_reduced(state) && first != last; ++first) {
      state = reducer(std::move(state), *first);
    }
    return state;
  }

  return result_t { initial };
}

template <typename ReducerT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputRangeTs>
auto reduce_nested_variadic_impl(ReducerT&& reducer,
                                 StateT&& initial,
                                 estd::index_sequence<Indices...>,
                                 InputRangeTs&& ...ranges)
  -> estd::decay_t<decltype(reducer(initial, *std::begin(ranges)...))>
{
  using result_t = estd::decay_t<decltype(
    reducer(initial, *std::begin(ranges)...))>;

  auto firsts = std::make_tuple(std::begin(ranges)...);
  auto lasts  = std::make_tuple(std::end(ranges)...);
  if (std::min({std::get<Indices>(firsts) !=
                std::get<Indices>(lasts)...}))
  {
    auto state = reducer(std::forward<StateT>(initial),
                         *std::get<Indices>(firsts)...);
    while (!state_is_reduced(state)
           && std::min({ ++std::get<Indices>(firsts) !=
                         std::get<Indices>(lasts)... })) {
      state = reducer(std::move(state), *std::get<Indices>(firsts)...);
    }
    return state;
  }

  return result_t { initial };
}

template <typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce_nested_variadic(ReducerT&& reducer, StateT&& state, InputRangeTs&& ...ranges)
  -> decltype(detail::reduce_nested_variadic_impl(
                std::forward<ReducerT>(reducer),
                std::forward<StateT>(state),
                estd::make_index_sequence<sizeof...(InputRangeTs)> {},
                std::forward<InputRangeTs>(ranges)...))
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
  return state_complete(
    reduce_nested(
      std::forward<ReducerT>(reducer),
      std::forward<StateT>(state),
      std::forward<InputRangeTs>(ranges)...));
}

} // namespace xform
} // namespace atria
