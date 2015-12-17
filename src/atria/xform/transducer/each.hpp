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
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

namespace detail {

struct each_rf_gen
{
  template <typename ReducingFnT,
            typename ActionT>
  struct apply
  {
    ReducingFnT step;
    ActionT action;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(step(std::forward<State>(s), std::forward<Inputs>(is)...))
    {
      estd::invoke(action, is...);
      return step(std::forward<State>(s),  std::forward<Inputs>(is)...);
    }
  };
};

} // namespace detail

template <typename T>
using each_t = transducer_impl<detail::each_rf_gen, T>;

/*!
 * Transducer that evaluates `action` on each input, forwarding the
 * input down the original inputs down the transducer chain.
 */
template <typename ActionT>
auto each(ActionT&& action)
  -> each_t<estd::decay_t<ActionT> >
{
  return each_t<estd::decay_t<ActionT> > {
    std::forward<ActionT>(action) };
}

} // namespace xform
} // namespace atria
