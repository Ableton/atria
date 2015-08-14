// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/any_state.hpp>
#include <atria/meta/lazy_enable_if.hpp>

namespace atria {
namespace xform {

/*!
 * Given a value `st` that represents the state of a reduction, this
 * function generically dispatches to the right function `UnwrappedFn`
 * or `WrappedFn`, depending of whether the value is already wrapped
 * or not.  This is, during the first iteration of the reduction,
 * `UnwrappedFn` will be called, from then on, `WrappedFnT` will be
 * called.
 *
 * The signatures should be of the form:
 *
 *   - `UnwrappedFn : A -> B`
 *   - `WrappedFn   : B -> B`
 *
 * This function can dispatch both statically and dynamically in a
 * transparent way.  It is thus very useful for writing stateful
 * transducers that can be type erased in a `transducer<>` object.
 *
 * @see transducer
 * @see take
 */
template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&&, WrappedFn&& fn)
  -> meta::lazy_enable_if_t<
    !std::is_same<
      estd::decay_t<StateT>,
      estd::decay_t<decltype(state_complete(st))>
    >::value,
    std::result_of<WrappedFn(StateT)>
  >
{
  return std::forward<WrappedFn>(fn)(std::forward<StateT>(st));
};

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&& fn, WrappedFn&&)
  -> meta::lazy_enable_if_t<
    !std::is_same<estd::decay_t<StateT>, any_state>::value
    && std::is_same<
      estd::decay_t<StateT>,
      estd::decay_t<decltype(state_complete(st))>
    >::value,
    std::result_of<UnwrappedFn(StateT)>
  >
{
  return std::forward<UnwrappedFn>(fn)(std::forward<StateT>(st));
};

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&& fn1, WrappedFn&& fn2)
  -> meta::lazy_enable_if_t<
    std::is_same<
      estd::decay_t<StateT>,
      any_state
    >::value,
    std::result_of<UnwrappedFn(StateT)>
  >
{
  using wrapped_state_t = estd::result_of_t<UnwrappedFn(StateT)>;

  if (!st.template has<wrapped_state_t>()) {
    return std::forward<UnwrappedFn>(fn1)(
      std::forward<StateT>(st));
  } else {
    return std::forward<WrappedFn>(fn2)(
      std::forward<StateT>(st).template as<wrapped_state_t>());
  }
};

} // namespace xform
} // namespace atria
