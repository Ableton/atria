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

#include <atria/meta/utils.hpp>
#include <iostream>

namespace atria {
namespace prelude {

/*!
 * Prints "<message> <x>" to `std::cerr` and returns the value,
 * forwarded.  Useful for looking at the value that is returned in the
 * middle of an expression.
 *
 * @see tracer
 * @see traced
 */
template <typename T>
auto trace(T&& x, const std::string& message)
  -> ABL_DECLTYPE_RETURN(
    (std::cerr << message << " " << x << std::endl,
     std::forward<T>(x)))

/*!
 * Function object for calling @a trace
 *
 * @see trace
 * @see traced
 */
struct tracer
{
  std::string message;

  template <typename T>
  auto operator() (T&& x)
    -> ABL_DECLTYPE_RETURN(
    trace(std::forward<T>(x), message))
};

} // namespace prelude

using prelude::tracer;
using prelude::trace;

} // namespace atria
