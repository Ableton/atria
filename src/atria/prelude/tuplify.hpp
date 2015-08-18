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
#include <tuple>

namespace atria {
namespace prelude {

/*!
 * Function that forwards its argument if only one element passed,
 * otherwise it makes a tuple.
 */
constexpr struct tuplify_t
{
  constexpr auto operator() () const
    -> ABL_DECLTYPE_RETURN(
      std::tuple<>{})

  template <typename InputT>
  constexpr auto operator() (InputT&& in) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<InputT>(in))

  template <typename InputT, typename ...InputTs>
  constexpr auto operator() (InputT&& in, InputTs&& ...ins) const
    -> ABL_DECLTYPE_RETURN(
      std::make_tuple(std::forward<InputT>(in),
                      std::forward<InputTs>(ins)...))
} tuplify {};

} // namespace prelude

using prelude::tuplify_t;
using prelude::tuplify;

} // namespace atria
