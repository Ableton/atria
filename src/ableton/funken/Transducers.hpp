// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/base/meta/Utils.hpp>
#include <ableton/estd/type_traits.hpp>
#include <ableton/estd/utility.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/reverse_fold.hpp>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <iterator>

namespace ableton {
namespace funken {

namespace detail {

struct ComposedReducer
{
  template <typename State, typename Fn>
  auto operator()(State&& state, Fn&& next)
    -> decltype(next(std::forward<State>(state)))
  {
    return next(std::forward<State>(state));
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
auto comp(Fn&& fn, Fns&& ...fns)
  -> detail::Composed<estd::decay_t<Fn>, estd::decay_t<Fns>...>
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
// Similar to clojure.core/identity
//
constexpr struct Identity
{
  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const
    -> decltype(std::forward<ArgT>(x))
  {
    return std::forward<ArgT>(x);
  }
} identity {};

//!
// Function that forwards its argument if only one element passed,
// otherwise it makes a tuple.
//
constexpr struct ZipF
{
  template <typename InputT>
  constexpr auto operator() (InputT&& in) const
    -> decltype(std::forward<InputT>(in))
  {
    return std::forward<InputT>(in);
  }

  template <typename ...InputTs>
  constexpr auto operator() (InputTs&& ...ins) const
    -> estd::enable_if_t<
      (sizeof...(InputTs) > 1),
      decltype(std::make_tuple(std::forward<InputTs>(ins)...))
    >
  {
    return std::make_tuple(std::forward<InputTs>(ins)...);
  }
} zipF {};

//!
// Reducer that collapses multiple inputs into tuples.  When used on a
// single sequence it is an identity.
//
constexpr struct ZipR
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&&, InputTs&& ...ins) const
    -> decltype(zipF(std::forward<InputTs>(ins)...))
  {
    return zipF(std::forward<InputTs>(ins)...);
  }
} zipR {};

//!
// Reducer that outputs to the iterator that is passed as state.
//
constexpr struct OutputR
{
  template <typename OutputItT, typename ...InputTs>
  auto operator() (OutputItT it, InputTs&& ...ins) const
    -> OutputItT
  {
    *it = zipF(std::forward<InputTs>(ins)...);
    return ++it;
  }
} outputR {};

namespace detail {

template <typename ReducerT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputRangeTs>
StateT reduce(ReducerT&& reducer,
              StateT state,
              estd::index_sequence<Indices...>,
              InputRangeTs&& ...ranges)
{
  for (auto firsts = std::make_tuple(std::begin(ranges)...),
            lasts  = std::make_tuple(std::end(ranges)...);
       std::min({ std::get<Indices>(firsts) !=
                  std::get<Indices>(lasts)... });
       base::meta::noop(++std::get<Indices>(firsts)...))
  {
    state = std::forward<ReducerT>(reducer)(
      state,
      *std::get<Indices>(firsts)...);
  }
  return state;
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
  -> estd::decay_t<StateT>
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
    (sizeof...(InputRangeTs) > 1),
    estd::decay_t<StateT>
  >
{
  return detail::reduce(
    std::forward<ReducerT>(reducer),
    std::forward<StateT>(state),
    estd::make_index_sequence<sizeof...(InputRangeTs)> {},
    std::forward<InputRangeTs>(ranges)...);
}

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
  -> decltype(std::forward<CollectionT>(col))
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
