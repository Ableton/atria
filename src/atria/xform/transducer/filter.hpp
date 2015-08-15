// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/skip.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto filter = [](auto predicate) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      return estd::invoke(predicate, is...)
        ? call(step, ABL_FORWARD(s), ABL_FORWARD(is)...)
        : skip(step, ABL_FORWARD(s), ABL_FORWARD(is)...);
    };
  };
};

#else // ABL_CXX14

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
        estd::invoke(predicate, is...)
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

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
