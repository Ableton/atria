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

#include <utility>
#include <atria/meta/utils.hpp>
#include <atria/estd/type_traits.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace prelude {

template <typename FnT>
struct complement_t
{
  FnT fn;

  template <typename... ArgTs>
  auto operator() (ArgTs&& ...args)
    -> ABL_DECLTYPE_RETURN(
      !estd::invoke(fn, std::forward<ArgTs>(args)...))
};

/*!
 * Similar to clojure.core/complement$1
 *
 * `fn` is invoked via standard *INVOKE*, allowing to negate function
 * pointers, member functions, etc.
 */
template <typename FnT>
auto complement(FnT&& fn)
  -> complement_t<estd::decay_t<FnT> >
{
  return { std::forward<FnT>(fn) };
}

} // namespace prelude

using prelude::complement_t;
using prelude::complement;

} // namespace atria
