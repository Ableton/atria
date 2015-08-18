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
