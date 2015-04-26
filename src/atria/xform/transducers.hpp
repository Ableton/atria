// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/reduced.hpp>
#include <atria/xform/reduce.hpp>
#include <atria/meta/common_type.hpp>
#include <atria/estd/type_traits.hpp>
#include <atria/estd/utility.hpp>

#include <cassert>

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
// in the next standard).  The `transducer_impl` type implements the first
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
struct transducer_impl : std::tuple<ParamTs...>
{
  using base_t = std::tuple<ParamTs...>;
  using base_t::base_t;

  template <typename ...Ts>
  constexpr transducer_impl(Ts&& ...ts)
    : base_t(std::forward<Ts>(ts)...)
  {}

  template<typename ReducerT>
  constexpr auto operator() (ReducerT&& reducer) const
    -> typename ReducerGenT::template apply<
      estd::decay_t<ReducerT>,
      estd::decay_t<ParamTs>...
    >
  {
    using indexes_t = estd::make_index_sequence<sizeof...(ParamTs)>;
    return this->make(std::forward<ReducerT>(reducer), indexes_t());
  }

  template<typename ReducerT, std::size_t...indexes_t>
  constexpr auto make(ReducerT&& reducer, estd::index_sequence<indexes_t...>) const
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

struct cat_reducer
{
  template <typename ReducerT>
  struct apply
  {
    ReducerT reducer;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(reduce_nested(reducer,
                                std::forward<State>(s),
                                std::forward<Inputs>(is)...))
    {
      return reduce_nested(reducer,
                           std::forward<State>(s),
                           std::forward<Inputs>(is)...);
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
      if (n > 1)
      {
        --n;
        return reducer(std::forward<State>(s),
                       std::forward<Inputs>(is)...);
      }
      else if (n == 1) {
        return reduced(
          reducer(std::forward<State>(s),
                  std::forward<Inputs>(is)...));
      } else {
        assert(false);
        return s;
      }
    }
  };
};

} // namespace detail

//!
// Similar to clojure.core/map$1
//
template <typename MappingT>
auto map(MappingT&& mapping)
  -> detail::transducer_impl<detail::map_reducer, estd::decay_t<MappingT> >
{
  return std::forward<MappingT>(mapping);
}

//!
// Similar to clojure.core/cat
//
constexpr auto cat = detail::transducer_impl<detail::cat_reducer> {};

//!
// Similar to clojure.core/mapcat$1
//
template <typename MappingT>
auto mapcat(MappingT&& mapping)
  -> decltype(comp(
                cat,
                map(std::forward<MappingT>(mapping))))
{
  return comp(
    cat,
    map(std::forward<MappingT>(mapping)));
}

//!
// Similar to clojure.core/take$1
//
template <typename IntegralT>
auto take(IntegralT&& n)
  -> detail::transducer_impl<detail::take_reducer, estd::decay_t<IntegralT> >
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
  -> detail::transducer_impl<detail::filter_reducer, estd::decay_t<PredicateT> >
{
  return std::forward<PredicateT>(predicate);
}

} // namespace xform
} // namespace atria
