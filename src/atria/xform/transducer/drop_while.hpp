// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/skip.hpp>
#include <atria/prelude/constantly.hpp>

namespace atria {
namespace xform {

namespace detail {

struct drop_while_rf_gen
{
  template <typename ReducingFnT,
            typename PredicateT>
  struct apply
  {
    ReducingFnT step;
    PredicateT predicate;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state(call(step, state_unwrap(std::forward<StateT>(s)),
                        std::forward<InputTs>(is)...),
                   bool{}))
    {
      auto taking =
           state_data(std::forward<StateT>(s), constantly(false))
        || !predicate(is...);

      return wrap_state(
          taking
            ? call(step,
                   state_unwrap(std::forward<StateT>(s)),
                   std::forward<InputTs>(is)...)
            : skip(step,
                   state_unwrap(std::forward<StateT>(s)),
                   std::forward<InputTs>(is)...),
          taking);
    }
  };
};

} // namespace detail

template <typename T>
using drop_while_t = transducer_impl<detail::drop_while_rf_gen, T>;

/*!
 * Similar to clojure.core/drop_while$1
 */
template <typename PredicateT>
auto drop_while(PredicateT&& n)
  -> drop_while_t<estd::decay_t<PredicateT> >
{
  return drop_while_t<estd::decay_t<PredicateT> > {
    std::forward<PredicateT>(n) };
}

} // namespace xform
} // namespace atria
