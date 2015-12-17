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

#include <atria/xform/into.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/xform/meta.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/meta/value_type.hpp>
#include <vector>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/into-array
 */
template <typename XformT,
          typename ...InputRangeTs>
auto into_vector(XformT&& xform, InputRangeTs&& ...ranges)
  -> std::vector<result_of_t<XformT, meta::value_t<InputRangeTs>... > >
{
  return into(
    std::vector<result_of_t<XformT, meta::value_t<InputRangeTs>... > >{},
    std::forward<XformT>(xform),
    std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
