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

namespace atria {
namespace prelude {

/*!
 * Similar to clojure.core/identity
 */
constexpr struct identity_t
{
  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<ArgT>(x))
} identity {};

/*!
 * Similar to @a identity, but it never returns a reference to the
 * pased in value.
 */
constexpr struct identity_t_
{
  template <typename ArgT>
  constexpr auto operator() (ArgT x) const -> ArgT
  {
    return x;
  }
} identity_ {};

} // namespace prelude

using prelude::identity_t;
using prelude::identity;
using prelude::identity_t_;
using prelude::identity_;

} // namespace atria
