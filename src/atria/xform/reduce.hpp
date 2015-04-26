// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

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

//!
// Box for a value that is `finished` reducing. It might be returned
// by reducers that might know that they are done before processing
// all the input, for example, when the state reaches an idempotent
// value.
//
// @see take
//
template <typename T>
struct reduced_t
{
  T value;
};

//!
// Constructs a reduced value for `value`
//
template <typename T>
auto reduced(T&& value) -> reduced_t<estd::decay_t<T> >
{
  return { std::forward<T>(value) };
}

//!
// Unwraps the value in a potentially *reduced* box.
// @see reduced_t
// @see maybe_reduced
//
template <typename T>
auto from_reduced(T& v) -> T& { return v; }
template <typename T>
auto from_reduced(const T& v) -> const T& { return v; }
template <typename T>
auto from_reduced(reduced_t<T>& v) -> T& { return v.value; }
template <typename T>
auto from_reduced(const reduced_t<T>& v) -> const T& { return v.value; }

//!
// Returns whether all values of a type are finished reducing.
// @see reduced_t
//
template <typename T>
struct type_is_reduced : std::false_type {};
template <typename T>
struct type_is_reduced<reduced_t<T>> : std::true_type {};

//!
// Returns whether a value `v` is a finished reduction.
// @see reduced_t
//
template <typename T>
auto is_reduced(const T&)
  -> estd::enable_if_t<!type_is_reduced<T>::value, bool>
{
  return false;
}

template <typename T>
auto is_reduced(const T&)
  -> estd::enable_if_t<type_is_reduced<T>::value, bool>
{
  return true;
}

//!
// Holds a value that may or may not be a finished reduction.  It
// is convertible from any other type that may be reduced.
// @see reduced_t
//
template <typename T>
struct maybe_reduced
{
  bool reduced;
  T value;

  template <typename U>
  maybe_reduced(U x)
    : reduced(is_reduced(x))
    , value(std::move(from_reduced(x)))
  {}
};

template <typename T>
auto is_reduced(const maybe_reduced<T>& v) -> bool { return v.reduced; }
template <typename T>
auto from_reduced(maybe_reduced<T>& v) -> T& { return v.value; }
template <typename T>
auto from_reduced(const maybe_reduced<T>& v) -> const T& { return v.value; }

namespace detail {

template <typename ReducerT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputRangeTs>
auto reduce(ReducerT&& reducer,
            StateT&& initial,
            estd::index_sequence<Indices...>,
            InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  using final_state_t = estd::decay_t<decltype(
    reducer(initial, *ranges.begin()...))>;

  auto state = final_state_t(std::forward<StateT>(initial));

  for (auto firsts = std::make_tuple(std::begin(ranges)...),
            lasts  = std::make_tuple(std::end(ranges)...);
       !is_reduced(state) &&
         std::min({ std::get<Indices>(firsts) !=
                    std::get<Indices>(lasts)... });
       meta::noop(++std::get<Indices>(firsts)...))
  {
    state = reducer(from_reduced(state),
                    *std::get<Indices>(firsts)...);
  }

  return from_reduced(state);
}

} // namespace detail

//!
// Similar to clojure.core/reduce.  Unlike `std::accumulate`, this
// reduces over a range (doesn't take to distinct iterators) and can
// reduce over several ranges at the same time.
//

#if ABL_REDUCE_WITH_ACCUMULATE

template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce(ReducerT&& reducer, StateT&& state, InputRangeT&& range)
  -> estd::decay_t<StateT>
{
  return std::accumulate(
    std::begin(range),
    std::end(range),
    std::forward<StateT>(state),
    std::forward<ReducerT>(reducer));
}

#endif // ABL_REDUCE_WITH_ACCUMULATE

#if !ABL_REDUCE_WITH_ACCUMULATE && ABL_REDUCE_NON_VARIADIC

template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce(ReducerT&& reducer, StateT&& initial, InputRangeT&& range)
  -> estd::decay_t<StateT>
{
  using final_state_t = estd::decay_t<decltype(
    reducer(initial, *range.begin()))>;

  auto state = final_state_t(std::forward<StateT>(initial));
  for (auto first = std::begin(range),
            last  = std::end(range);
       !is_reduced(state) && first != last;
       ++first)
  {
    state = reducer(from_reduced(state), *first);
  }
  return from_reduced(state);
}

#endif // !ABL_REDUCE_WITH_ACCUMULATE && ABL_REDUCE_NON_VARIADIC

//!
// Variadic overload of `reduce()`
//
template <typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducerT&& reducer, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::enable_if_t<
    (sizeof...(InputRangeTs) > 1)
    || !ABL_REDUCE_NON_VARIADIC,
    estd::decay_t<StateT>
  >
{
  return detail::reduce(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    estd::make_index_sequence<sizeof...(InputRangeTs)> {},
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
