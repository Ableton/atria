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

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/with_state.hpp>
#include <atria/meta/copy_traits.hpp>
#include <atria/prelude/constantly.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto take_nth = [](auto nth) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      return with_state(
        ABL_FORWARD(s),
        [&](auto&& st)
        {
          return wrap_state(
            step(ABL_FORWARD(st), ABL_FORWARD(is)...),
            1);
        },
        [&](auto&& st)
        {
          auto count = state_wrapper_data(ABL_FORWARD(st));
          return count != nth
            ? wrap_state(
              state_unwrap(ABL_FORWARD(st)),
              count + 1)
            : wrap_state(
              step(state_unwrap(ABL_FORWARD(st)), ABL_FORWARD(is)...),
              1);
        });
    };
  };
};

#else // ABL_CXX14

namespace detail {

struct take_nth_rf_gen
{
  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT nth;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), is...), nth))
    {
      using result_t   = decltype(wrap_state(step(state_unwrap(s), is...), nth));
      using complete_t = decltype(state_complete(s));

      using wrapped_t   = meta::copy_decay_t<StateT, estd::decay_t<result_t>>;
      using unwrapped_t = meta::copy_decay_t<StateT, estd::decay_t<complete_t>>;

      return with_state(
        std::forward<StateT>(s),
        [&](unwrapped_t&& st)
        {
          return wrap_state(
            step(std::forward<unwrapped_t>(st),
                 std::forward<InputTs>(is)...),
            1);
        },
        [&](wrapped_t&& st)
        {
          auto count = state_wrapper_data(std::forward<wrapped_t>(st));
          return count != nth
            ? wrap_state(
              state_unwrap(std::forward<wrapped_t>(st)),
              count + 1)
            : wrap_state(
              step(state_unwrap(std::forward<wrapped_t>(st)),
                   std::forward<InputTs>(is)...),
              1);
        });
    }
  };
};

} // namespace detail

template <typename T>
using take_nth_t = transducer_impl<detail::take_nth_rf_gen, T>;

/*!
 * Similar to clojure.core/take_nth$1
 */
template <typename IntegralT>
auto take_nth(IntegralT&& n)
  -> take_nth_t<estd::decay_t<IntegralT> >
{
  return take_nth_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(n) };
}

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
