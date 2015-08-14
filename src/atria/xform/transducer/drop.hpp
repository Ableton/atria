// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/skip.hpp>
#include <atria/prelude/constantly.hpp>

namespace atria {
namespace xform {

namespace detail {

struct drop_rf_gen
{
  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT total;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state(call(step, state_unwrap(std::forward<StateT>(s)),
                        std::forward<InputTs>(is)...),
                   total))
    {
      auto count = state_data(std::forward<StateT>(s),
                              constantly(total));
      return count != 0
        ? wrap_state(
          skip(step,
               state_unwrap(std::forward<StateT>(s)),
               std::forward<InputTs>(is)...),
          count - 1)
        : wrap_state(
          call(step,
               state_unwrap(std::forward<StateT>(s)),
               std::forward<InputTs>(is)...),
          count);
    }
  };
};

} // namespace detail

template <typename T>
using drop_t = transducer_impl<detail::drop_rf_gen, T>;

/*!
 * Similar to clojure.core/drop$1
 */
template <typename IntegralT>
auto drop(IntegralT&& n)
  -> drop_t<estd::decay_t<IntegralT> >
{
  return drop_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(n) };
}

} // namespace xform
} // namespace atria
