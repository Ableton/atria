// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/estd/type_traits.hpp>
#include <ableton/estd/utility.hpp>
#include <algorithm>
#include <numeric>
#include <tuple>

//!
// When defined to 1, std::accumulate will be used as an
// implementation for reduce() over one single collection.  In that
// case, halting reducers (e.g. take) might not work.
//
#define ABL_REDUCE_WITH_ACCUMULATE 0

namespace ableton {
namespace funken {

//!
// Box for a value that is `finished` reducing. It might be returned
// by reducers that might know that they are done before processing
// all the input, for example, when the state reaches an idempotent
// value.
//
// @see take
//
template <typename T>
struct Reduced
{
  T value;
};

//!
// Constructs a reduced value for `value`
//
template <typename T>
auto reduced(T&& value) -> Reduced<estd::decay_t<T> >
{
  return { std::forward<T>(value) };
}

//!
// Unwraps the value in a potentially *reduced* box.
// @see Reduced
// @see MaybeReduced
//
template <typename T>
auto fromReduced(T& v) -> T& { return v; }
template <typename T>
auto fromReduced(const T& v) -> const T& { return v; }
template <typename T>
auto fromReduced(Reduced<T>& v) -> T& { return v.value; }
template <typename T>
auto fromReduced(const Reduced<T>& v) -> const T& { return v.value; }

//!
// Returns whether all values of a type are finished reducing.
// @see Reduced
//
template <typename T>
struct TypeIsReduced : std::false_type {};
template <typename T>
struct TypeIsReduced<Reduced<T>> : std::true_type {};

//!
// Returns whether a value `v` is a finished reduction.
// @see Reduced
//
template <typename T>
auto isReduced(const T&)
  -> estd::enable_if_t<!TypeIsReduced<T>::value, bool>
{
  return false;
}

template <typename T>
auto isReduced(const T&)
  -> estd::enable_if_t<TypeIsReduced<T>::value, bool>
{
  return true;
}

//!
// Holds a value that may or may not be a finished reduction.  It
// is convertible from any other type that may be reduced.
// @see Reduced
//
template <typename T>
struct MaybeReduced
{
  bool reduced;
  T value;

  template <typename U>
  MaybeReduced(U x)
    : reduced(isReduced(x))
    , value(std::move(fromReduced(x)))
  {}
};

template <typename T>
auto isReduced(const MaybeReduced<T>& v) -> bool { return v.reduced; }
template <typename T>
auto fromReduced(MaybeReduced<T>& v) -> T& { return v.value; }
template <typename T>
auto fromReduced(const MaybeReduced<T>& v) -> const T& { return v.value; }

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
  using FinalStateT = estd::decay_t<decltype(
    reducer(initial, *ranges.begin()...))>;

  auto state = FinalStateT(std::forward<StateT>(initial));

  for (auto firsts = std::make_tuple(std::begin(ranges)...),
            lasts  = std::make_tuple(std::end(ranges)...);
       !isReduced(state) &&
         std::min({ std::get<Indices>(firsts) !=
                    std::get<Indices>(lasts)... });
       base::meta::noop(++std::get<Indices>(firsts)...))
  {
    state = reducer(fromReduced(state),
                    *std::get<Indices>(firsts)...);
  }

  return fromReduced(state);
}

} // namespace detail

//!
// Similar to clojure.core/reduce.  Unlike `std::accumulate`, this
// reduces over a range (doesn't take to distinct iterators) and can
// reduce over several ranges at the same time.
//
template <typename ReducerT,
          typename StateT,
          typename InputRangeT>
auto reduce(ReducerT&& reducer, StateT&& state, InputRangeT&& range)
  -> estd::enable_if_t<
  ABL_REDUCE_WITH_ACCUMULATE,
  estd::decay_t<StateT> >
{
  return std::accumulate(
    std::begin(range),
    std::end(range),
    std::forward<StateT>(state),
    std::forward<ReducerT>(reducer));
}

//!
// Variadic overload of `reduce()`
//
template <typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducerT&& reducer, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::enable_if_t<
    (sizeof...(InputRangeTs) > 1) || !ABL_REDUCE_WITH_ACCUMULATE,
    estd::decay_t<StateT>
  >
{
  return detail::reduce(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    estd::make_index_sequence<sizeof...(InputRangeTs)> {},
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace funken
} // namespace ableton
