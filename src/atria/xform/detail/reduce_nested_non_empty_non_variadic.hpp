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

#include <iterator>
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty_non_variadic(ReducingFnT&& step,
                                          StateT&& initial,
                                          InputRangeT&& range)
  -> estd::decay_t<decltype(step(initial, *std::begin(range)))>
{
  auto first = std::begin(range);
  auto last  = std::end(range);
  auto state = step(std::forward<StateT>(initial), *first);
  // This may be expressed more brief with a:
  //    while(++first != last)
  // but the for loop seems to make compilers generate better code.
  for (++first; !state_is_reduced(state) && first != last; ++first) {
    // `x = std::move(x)` is undefined behaviour, hence the two
    // steps approach to protect for when `step` just forwards
    // the state back.
    auto new_state = step(std::move(state), *first);
    state = std::move(new_state);
  }
  return state;
}

} // namespace detail
} // namespace xform
} // namespace atria
