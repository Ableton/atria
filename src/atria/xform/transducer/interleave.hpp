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
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {

namespace detail {

struct interleave_rf_gen
{
  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    template <typename StateT>
    auto impl(StateT&& s) -> StateT&&
    {
      return std::forward<StateT>(s);
    }

    template <typename StateT, typename InputT, typename ...InputTs>
    auto impl(StateT&& s, InputT&& i, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s), std::forward<InputT>(i)))
    {
      return !state_is_reduced(s)
        ? impl(step(std::forward<StateT>(s), std::forward<InputT>(i)),
               std::forward<InputTs>(is)...)
        : std::forward<StateT>(s);
    }

    template <typename StateT, typename InputT, typename ...InputTs>
    auto operator() (StateT&& s, InputT&& i, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s), std::forward<InputT>(i)))
    {
      return impl(step(std::forward<StateT>(s), std::forward<InputT>(i)),
                  std::forward<InputTs>(is)...);
    }
  };
};

} // namespace detail

using interleave_t = transducer_impl<detail::interleave_rf_gen>;

/*!
 * Similar to clojure.core/interleave$1
 */
constexpr auto interleave = interleave_t {};

} // namespace xform
} // namespace atria
