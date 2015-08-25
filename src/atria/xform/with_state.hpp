//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

#include <atria/xform/any_state.hpp>
#include <atria/meta/lazy_enable_if.hpp>

namespace atria {
namespace xform {
namespace detail {

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state_check_state_complete(std::false_type /*is_state_complete*/, StateT&& st, UnwrappedFn&&, WrappedFn&& fn)
  -> ABL_DECLTYPE_RETURN(
    std::forward<WrappedFn>(fn)(std::forward<StateT>(st)))

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state_check_state_complete(std::true_type /*is_state_complete*/, StateT&& st, UnwrappedFn&& fn, WrappedFn&&)
  -> ABL_DECLTYPE_RETURN(
    std::forward<UnwrappedFn>(fn)(std::forward<StateT>(st)))

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state_check_any_state(std::false_type /*is_any_state*/, StateT&& st, UnwrappedFn&& fn1, WrappedFn&& fn2)
  -> ABL_DECLTYPE_RETURN(
    with_state_check_state_complete(
      std::is_same<
        estd::decay_t<StateT>,
        estd::decay_t<decltype(state_complete(std::forward<StateT>(st)))>
      >{},
      std::forward<StateT>(st),
      std::forward<UnwrappedFn>(fn1),
      std::forward<WrappedFn>(fn2)))

template <typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state_check_any_state(std::true_type /*is_any_state*/, StateT&& st, UnwrappedFn&& fn1, WrappedFn&& fn2)
  -> decltype(std::forward<UnwrappedFn>(fn1)(std::forward<StateT>(st)))
{
  using wrapped_state_t = estd::result_of_t<UnwrappedFn(StateT)>;

  if (!st.template has<wrapped_state_t>()) {
    return std::forward<UnwrappedFn>(fn1)(
      std::forward<StateT>(st));
  } else {
    return std::forward<WrappedFn>(fn2)(
      std::forward<StateT>(st).template as<wrapped_state_t>());
  }
}

} // namespace detail

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
auto with_state(StateT&& st, UnwrappedFn&& fn1, WrappedFn&& fn2)
  -> ABL_DECLTYPE_RETURN(
    detail::with_state_check_any_state(
      std::is_same<estd::decay_t<StateT>, any_state>{},
      std::forward<StateT>(st),
      std::forward<UnwrappedFn>(fn1),
      std::forward<WrappedFn>(fn2)))

} // namespace xform
} // namespace atria
