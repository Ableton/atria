// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/skip.hpp>

namespace atria {
namespace xform {

namespace detail {

struct filter_rf_gen
{
  template <typename ReducingFnT,
            typename PredicateT>
  struct apply
  {
    ReducingFnT step;
    PredicateT predicate;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        predicate(is...)
          ? call(step, std::forward<State>(s), std::forward<Inputs>(is)...)
          : skip(step, std::forward<State>(s), std::forward<Inputs>(is)...))
  };
};

} // namespace detail

template <typename T>
using filter_t = transducer_impl<detail::filter_rf_gen, T>;

/*!
 * Similar to clojure.core/filter$1
 */
template <typename PredicateT>
auto filter(PredicateT&& predicate)
  -> filter_t<estd::decay_t<PredicateT> >
{
  return filter_t<estd::decay_t<PredicateT> > {
    std::forward<PredicateT>(predicate) };
}

} // namespace xform
} // namespace atria
