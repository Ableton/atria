// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/reduce.hpp>
#include <atria/xform/functional.hpp>
#include <atria/meta/utils.hpp>
#include <atria/meta/common_type.hpp>
#include <atria/estd/utility.hpp>
#include <atria/estd/type_traits.hpp>
#include <algorithm>
#include <iterator>

namespace atria {
namespace xform {

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
// in the next standard).  The `transducer` type implements the first
// two calls. The `ReducerGenT` parameter should have a nested
// template `apply` that implements the last call.  It will be
// constructed `reducer, params...` and it should be callable with
// `state, input`.
//
// @see map
// @see filter
//
template<typename ReducerGenT,
         typename ...ParamTs>
struct transducer : std::tuple<ParamTs...>
{
  using base_t = std::tuple<ParamTs...>;
  using base_t::base_t;

  template <typename ...Ts>
  transducer(Ts&& ...ts)
    : base_t(std::forward<Ts>(ts)...)
  {}

  template<typename ReducerT>
  auto operator() (ReducerT&& reducer) const
    -> typename ReducerGenT::template apply<
      estd::decay_t<ReducerT>,
      estd::decay_t<ParamTs>...
    >
  {
    using indexes_t = estd::make_index_sequence<sizeof...(ParamTs)>;
    return this->make(std::forward<ReducerT>(reducer), indexes_t());
  }

  template<typename ReducerT, std::size_t...indexes_t>
  auto make(ReducerT&& reducer, estd::index_sequence<indexes_t...>) const
    -> typename ReducerGenT::template apply<
      estd::decay_t<ReducerT>,
      estd::decay_t<ParamTs>...
    >
  {
    return { std::forward<ReducerT>(reducer),
             std::get<indexes_t>(*this)... };
  }
};

struct map_reducer
{
  template <typename ReducerT,
            typename MappingT>
  struct apply
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

struct flat_map_reducer
{
  template <typename ReducerT,
            typename MappingT>
  struct apply
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

struct filter_reducer
{
  template <typename ReducerT,
            typename PredicateT>
  struct apply
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

struct take_reducer
{
  template <typename ReducerT,
            typename IntegralT>
  struct apply
  {
    ReducerT reducer;
    IntegralT n;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> maybe_reduced<estd::decay_t<
           meta::common_type_t<
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
  -> detail::transducer<detail::map_reducer, estd::decay_t<MappingT> >
{
  return std::forward<MappingT>(mapping);
}

//!
// Similar to clojure.core/mapcat$1
//
template <typename MappingT>
auto flat_map(MappingT&& mapping)
  -> detail::transducer<detail::flat_map_reducer, estd::decay_t<MappingT> >
{
  return std::forward<MappingT>(mapping);
}

//!
// Similar to clojure.core/take$1
//
template <typename IntegralT>
auto take(IntegralT&& n)
  -> detail::transducer<detail::take_reducer, estd::decay_t<IntegralT> >
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
  -> detail::transducer<detail::filter_reducer, estd::decay_t<PredicateT> >
{
  return std::forward<PredicateT>(predicate);
}

//!
// Reducer that returns the last input of the sequence.
//
constexpr struct last_r_t
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
} last_r {};

//!
// Reducer that outputs to the iterator that is passed as state.
//
constexpr struct output_r_t
{
  template <typename OutputItT, typename ...InputTs>
  auto operator() (OutputItT it, InputTs&& ...ins) const
    -> OutputItT
  {
    *it = tuplify(std::forward<InputTs>(ins)...);
    return ++it;
  }
} output_r {};


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
    output_r,
    std::back_inserter(col),
    std::forward<InputRangeTs>(ranges)...);
  return std::forward<CollectionT>(col);
}

} // namespace xform
} // namespace atria
