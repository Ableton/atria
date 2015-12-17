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

#include <atria/xform/transduce.hpp>
#include <atria/xform/reducing/first_rf.hpp>

namespace atria {
namespace xform {

namespace detail {

struct run_state_t {};

} // namespace detail

/*!
 * Runs a transducer composed with no significant reduction. It is
 * useful to execute a transducer for which we are only interested on
 * its side effects.
 */
template <typename XformT,
          typename ...InputRangeTs>
void run(XformT&& xform, InputRangeTs&& ...ranges)
{
  transduce(
    std::forward<XformT>(xform),
    first_rf,
    detail::run_state_t{},
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
