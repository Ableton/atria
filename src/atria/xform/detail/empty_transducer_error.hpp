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

#include <stdexcept>

namespace atria {
namespace xform {
namespace detail {

/*!
 * Error thrown by transducers when they are empty.  The problem is
 * that making an empty transducer requires skipping on the first
 * iteration.  Skipping comes with a cost.  So for performance
 * reasons, a transducer might choose to just rise an error if
 * produces a completely empty sequence.
 *
 * @note This is kept in `detail` because we want to explore
 *       alternative designs that do not require skipping.
 *
 * @see  skip
 *
 * @todo Explore alternative design.
 */
struct empty_transducer_error : std::runtime_error
{
  using base_t = std::runtime_error;
  using base_t::base_t;
  empty_transducer_error() : base_t("empty transducer") {}
};

/*!
 * Utility to check whether a range is empty and return it.
 */
template <typename RangeT>
auto check_non_empty(RangeT&& x) -> RangeT&&
{
  using std::begin;
  using std::end;
  if (begin(x) == end(x))
    throw empty_transducer_error{};
  return std::forward<RangeT>(x);
}


} // namespace detail
} // namespace xform
} // namespace atria
