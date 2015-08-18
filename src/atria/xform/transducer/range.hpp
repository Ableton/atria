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
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/count.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

/*!
 * Generator transducer version of Python `range`
 */
template <typename StopT>
constexpr auto range(StopT&& stop)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(),
      take(std::forward<StopT>(stop))))

template <typename StartT, typename StopT>
constexpr auto range(StartT&& start, StopT&& stop)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(start),
      take(std::max(decltype(stop - start){},
                    stop - start))))

template <typename StartT, typename StopT, typename StepT>
constexpr auto range(StartT&& start, StopT&& stop, StepT&& step)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(start, step),
      take(std::max(decltype((stop - start) / step){},
                    (stop - start) / step))))

} // namespace xform
} // namespace atria
