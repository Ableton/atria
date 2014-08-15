// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/estd/type_traits.hpp>
#include <ableton/estd/utility.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/reverse_fold.hpp>
#include <tuple>
#include <numeric>

namespace ableton {
namespace funken {

namespace detail {

struct ComposedReducer
{
  template <typename State, typename Fn>
  auto operator()(State&& state, Fn&& next)
    -> decltype(std::forward<Fn>(next)(std::forward<State>(state)))
  {
    return std::forward<Fn>(next)(std::forward<State>(state));
  }
};

template<typename Fn, typename ...Fns>
struct Composed : std::tuple<Fn, Fns...>
{
  using std::tuple<Fn, Fns...>::tuple;

  std::tuple<Fn, Fns...>& asTuple() { return *this; }
  const std::tuple<Fn, Fns...>& asTuple() const { return *this; }

  template <typename Arg>
  auto operator() (Arg&& arg) const
    -> decltype(boost::fusion::reverse_fold(
                  asTuple(), arg, ComposedReducer{}))
  {
    return boost::fusion::reverse_fold(
      asTuple(), arg, ComposedReducer{});
  }
};

} // namespace detail

//!
// Returns an object *g* that composes all the given functions *f_i*,
// such that:
//                 g(x) = f_1(f_2(...f_n(x)))
//
template <typename Fn, typename ...Fns>
detail::Composed<Fn, Fns...> comp(Fn&& fn, Fns&& ...fns)
{
  return { std::forward<Fn>(fn), std::forward<Fns>(fns)... };
};

namespace detail {

//!
// Utility to write simple transducers easily.  Most transducers have
// the following structure:
//
// @code{.hs}
//  xducer params... =     -- 1. this returns a transducer
//    \ reducer ->         -- 2. this is a transducer
//       \ state, input -> -- 3. this is transformed version of 'reducer'
//           f(params..., reducer, state, input)
// @endocde
//
// Writing functions that return functions without erasing their type
// is very cumbersome in C++11 (this is not true with decltype(auto)
// in the next standard).  The `Transducer` type implements the first
// two calls. The `ResultReducerT` parameter should implement the last
// call.  It will be constructed `reducer, params...` and it should be
// callable with `state, input`.
//
// @see map
// @see filter
//
template<template <class, class...> class ResultReducerT,
         typename ...ParamTs>
struct Transducer : std::tuple<ParamTs...>
{
  using std::tuple<ParamTs...>::tuple;

  template<typename ReducerT>
  auto operator() (ReducerT&& reducer) const
    -> ResultReducerT<ReducerT, ParamTs...>
  {
    using Indexes = estd::make_index_sequence<sizeof...(ParamTs)>;
    return this->make(std::forward<ReducerT>(reducer), Indexes());
  }

  template<typename ReducerT, std::size_t...Indexes>
  auto make(ReducerT&& reducer, estd::index_sequence<Indexes...>) const
    -> ResultReducerT<ReducerT, ParamTs...>
  {
    return { std::forward<ReducerT>(reducer),
             std::get<Indexes>(*this)... };
  }
};

template <typename ReducerT,
          typename MappingT>
struct MapReducer
{
  ReducerT reducer;
  MappingT mapping;

  template <typename State, typename Input>
  auto operator() (State&& s, Input&& i) const
    -> decltype(reducer(s, mapping(i)))
  {
    return reducer(s, mapping(i));
  }
};

template <typename ReducerT,
          typename PredicateT>
struct FilterReducer
{
  ReducerT reducer;
  PredicateT predicate;

  template <typename State, typename Input>
  auto operator() (State&& s, Input&& i) const
    -> decltype(predicate(i) ? reducer(s, i) : s)
  {
    return predicate(i) ? reducer(s, i) : s;
  }
};

} // namespace detail

//!
// Similar to clojure.core/map$1
//
template <typename MappingT>
auto map(MappingT&& mapping)
  -> detail::Transducer<detail::MapReducer, MappingT>
{
  return detail::Transducer<detail::MapReducer, MappingT> {
    std::forward<MappingT>(mapping) };
}

//!
// Similar to clojure.core/filter$1
//
template <typename PredicateT>
auto filter(PredicateT&& predicate)
  -> detail::Transducer<detail::FilterReducer, PredicateT>
{
  return detail::Transducer<detail::FilterReducer, PredicateT> {
    std::forward<PredicateT>(predicate) };
}

//!
// Similar to clojure.core/identity
//
constexpr struct Identity
{
  template <typename FirstT, typename ...RestT>
  constexpr auto operator() (FirstT&& x, RestT&&...) const
    -> decltype(std::forward<FirstT>(x))
  {
    return std::forward<FirstT>(x);
  }
} identity {};


//!
// Similar to clojure.core/transduce, but with parameter ordering more
// similar to those convetional in the C++ standard library.
//
template <typename InputRangeT,
          typename XformT,
          typename ReducerT,
          typename StateT>
StateT transduce(InputRangeT&& range, XformT&& xform,
                 ReducerT&& reducer, StateT&& state)
{
  auto xformed = xform(reducer);
  return std::accumulate(
    std::begin(range),
    std::end(range),
    state,
    xformed);
}

} // namespace funken
} // namespace ableton
