// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/prelude/constantly.hpp>

namespace atria {
namespace xform {

namespace detail {

struct count_rf_gen
{
  template <typename ReducingFnT,
            typename InitialT,
            typename StepT>
  struct apply
  {
    ReducingFnT step;
    InitialT initial;
    StepT count_step;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), is..., initial), initial))
    {
      auto count = state_data(std::forward<StateT>(s), constantly(initial));
      auto next  = count;
      next += count_step;
      return wrap_state(
        step(state_unwrap(std::forward<StateT>(s)),
             std::forward<InputTs>(is)...,
             std::move(count)),
        std::move(next));
    }
  };
};

} // namespace detail

template <typename T1, typename T2>
using count_t = transducer_impl<detail::count_rf_gen, T1, T2>;

/*!
 * Generator transducer produces a sequence:
 *
 *   $$init, init+step, ..., init+step*n$$
 *
 * It is inspired by Python's `itertools.count` generator.
 */
template <typename InitT=std::size_t, typename StepT=InitT>
constexpr auto count(InitT init = InitT{0}, StepT step = StepT{1})
  -> count_t<InitT, StepT>
{
  return count_t<InitT, StepT> { std::move(init), std::move(step) };
}

} // namespace xform
} // namespace atria
