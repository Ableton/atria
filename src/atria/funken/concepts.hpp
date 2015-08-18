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

#include <atria/meta/concept.hpp>
#include <atria/estd/type_traits.hpp>
#include <utility>
#include <cassert>

namespace atria {
namespace funken {

template <typename T>
auto declval_() -> typename std::add_rvalue_reference<T>::type
{
  assert(!"You should never run this function!");
  return *static_cast<estd::decay_t<T>*>(nullptr);
}

/*!
 * Concept for objects that provide values via a getter.
 */
ABL_CONCEPT_SPEC(In_value)
{
  template <typename T,
            typename V = estd::decay_t<estd::Value_type<T> > >
  auto requires_(T&& x, V& v = declval_<V&>()) -> decltype(
    meta::expressions(
      v = x.get(),
      v = static_cast<const T&&>(x).get()));
};

/*!
 * Concept for objects that provide values via a setter.
 */
ABL_CONCEPT_SPEC(Out_value)
{
  template <typename T,
            typename V = estd::Value_type<T> >
  auto requires_(T&& x, V& v = declval_<V&>()) -> decltype(
    meta::expressions(
      (x.set(v), meta::can_be_void),
      (x.set(static_cast<const V&&>(v)), meta::can_be_void)));
};

/*!
 * Concept for objects that meet boot `In_value` and `Out_value`.
 * @see In_value
 * @see Out_value
 */
ABL_CONCEPT_SPEC(Inout_value)
{
  template <typename T>
  auto requires_(T&& x) -> decltype(
    meta::expressions(
      meta::require<(In_value<T>())>(),
      meta::require<(Out_value<T>())>()));
};

/*!
 * Concept for values that can be commited.
 */
ABL_CONCEPT_SPEC(Root_value)
{
  template <typename T>
  auto requires_(T&& x) -> decltype(
    meta::expressions(
      (commit(x), meta::can_be_void)));
};

} // namespace funken
} // namespace atria
