// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/Reduce.hpp>
#include <ableton/funken/Functional.hpp>
#include <ableton/meta/Utils.hpp>
#include <ableton/meta/CommonType.hpp>
#include <ableton/estd/utility.hpp>
#include <ableton/estd/type_traits.hpp>
#include <algorithm>
#include <iterator>

namespace ableton {
namespace funken {

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
// two calls. The `ReducerGenT` parameter should have a nested
// template `Reducer` that implements the last call.  It will be
// constructed `reducer, params...` and it should be callable with
// `state, input`.
//
// @see map
// @see filter
//
template<typename ReducerGenT,
         typename ...ParamTs>
struct Transducer : std::tuple<ParamTs...>
{
  using std::tuple<ParamTs...>::tuple;

  template<typename ReducerT>
  auto operator() (ReducerT&& reducer) const
    -> typename ReducerGenT::template Reducer<
      estd::decay_t<ReducerT>,
      estd::decay_t<ParamTs>...
    >
  {
    using Indexes = estd::make_index_sequence<sizeof...(ParamTs)>;
    return this->make(std::forward<ReducerT>(reducer), Indexes());
  }

  template<typename ReducerT, std::size_t...Indexes>
  auto make(ReducerT&& reducer, estd::index_sequence<Indexes...>) const
    -> typename ReducerGenT::template Reducer<
      estd::decay_t<ReducerT>,
      estd::decay_t<ParamTs>...
    >
  {
    return { std::forward<ReducerT>(reducer),
             std::get<Indexes>(*this)... };
  }
};

struct MapReducer
{
  template <typename ReducerT,
            typename MappingT>
  struct Reducer
  {
    ReducerT reducer;
    MappingT mapping;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(reducer(std::forward<State>(s),
                          mapping(std::forward<Inputs>(is)...)))
    {
      return reducer(std::forward<State>(s),
                     mapping(std::forward<Inputs>(is)...));
    }
  };
};

struct FlatMapReducer
{
  template <typename ReducerT,
            typename MappingT>
  struct Reducer
  {
    ReducerT reducer;
    MappingT mapping;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(reduce(reducer, std::forward<State>(s),
                         mapping(std::forward<Inputs>(is)...)))
    {
      return reduce(reducer, std::forward<State>(s),
                    mapping(std::forward<Inputs>(is)...));
    }
  };
};

template <typename ResultT=void>
struct FilterReducer
{
  template <typename ReducerT,
            typename PredicateT>
  struct Reducer
  {
    ReducerT reducer;
    PredicateT predicate;

    using result_type = ResultT;

    template <typename State, typename ...Inputs>
    result_type operator() (State&& s, Inputs&& ...is)
    {
      if (predicate(std::forward<Inputs>(is)...))
        return reducer(std::forward<State>(s),
                       std::forward<Inputs>(is)...);
      return s;
    }
  };
};

template <>
struct FilterReducer<void>
{
  template <typename ReducerT,
            typename PredicateT>
  struct Reducer
  {
    ReducerT reducer;
    PredicateT predicate;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(true
                  ? reducer(std::forward<State>(s),
                            std::forward<Inputs>(is)...)
                  : std::forward<State>(s))
    {
      return predicate(std::forward<Inputs>(is)...)
        ? reducer(std::forward<State>(s),
                  std::forward<Inputs>(is)...)
        : std::forward<State>(s);
    }
  };
};

struct TakeReducer
{
  template <typename ReducerT,
            typename IntegralT>
  struct Reducer
  {
    ReducerT reducer;
    IntegralT n;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> MaybeReduced<estd::decay_t<
           meta::CommonType_t<
             decltype(s),
             decltype(reducer(s, is...)) > > >
    {
      if (n > 0)
      {
        --n;
        return reducer(std::forward<State>(s),
                       std::forward<Inputs>(is)...);
      }
      return reduced(std::forward<State>(s));
    }
  };
};

} // namespace detail

//!
// Similar to clojure.core/map$1
//
template <typename MappingT>
auto map(MappingT&& mapping)
  -> detail::Transducer<detail::MapReducer, estd::decay_t<MappingT> >
{
  return { std::forward<MappingT>(mapping) };
}

//!
// Similar to clojure.core/mapcat$1
//
template <typename MappingT>
auto flatMap(MappingT&& mapping)
  -> detail::Transducer<detail::FlatMapReducer, estd::decay_t<MappingT> >
{
  return std::forward<MappingT>(mapping);
}

//!
// Similar to clojure.core/take$1
//
template <typename IntegralT>
auto take(IntegralT&& n)
  -> detail::Transducer<detail::TakeReducer, estd::decay_t<IntegralT> >
{
  return n;
}

//!
// Similar to clojure.core/filter$1
// If no `ResultT` is given, the resulting reducers will try to deduce
// it from (true ? reducer(inputs...) : state), which might no be
// possible if state and inputs are incompatible.
//
template <typename ResultT=void, typename PredicateT>
auto filter(PredicateT&& predicate)
  -> detail::Transducer<detail::FilterReducer<ResultT>, estd::decay_t<PredicateT> >
{
  return std::forward<PredicateT>(predicate);
}

//!
// Reducer that returns the last input of the sequence.
//
constexpr struct lastR
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&&, InputTs&& ...ins) const
    -> estd::decay_t<decltype(tuplify(std::forward<InputTs>(ins)...))>
  {
    return tuplify(std::forward<InputTs>(ins)...);
  }

  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&& s) const -> StateT&&
  {
    return std::forward<StateT>(s);
  }
} lastR {};

//!
// Reducer that outputs to the iterator that is passed as state.
//
constexpr struct OutputR
{
  template <typename OutputItT, typename ...InputTs>
  auto operator() (OutputItT it, InputTs&& ...ins) const
    -> OutputItT
  {
    *it = tuplify(std::forward<InputTs>(ins)...);
    return ++it;
  }
} outputR {};


//!
// Similar to clojure.core/transduce
//
template <typename XformT,
          typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
StateT transduce(XformT&& xform, ReducerT&& reducer,
                 StateT&& state, InputRangeTs&& ...ranges)
{
  auto xformed = xform(std::forward<ReducerT>(reducer));
  return reduce(
    xformed,
    state,
    std::forward<InputRangeTs>(ranges)...);
}

//!
// Similar to clojure.core/transduce$4
//
template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> CollectionT&&
{
  transduce(
    std::forward<XformT>(xform),
    outputR,
    std::back_inserter(col),
    std::forward<InputRangeTs>(ranges)...);
  return std::forward<CollectionT>(col);
}

} // namespace funken
} // namespace ableton
