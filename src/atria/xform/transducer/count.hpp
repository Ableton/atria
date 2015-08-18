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
