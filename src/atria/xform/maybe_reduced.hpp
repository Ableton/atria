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

#include <atria/xform/state_wrapper.hpp>

namespace atria {
namespace xform {

/*!
 * Tag for `maybe_reduced` state wrapper.
 * @see maybe_reduced
 */
struct maybe_reduced_tag {};

/*!
 * State wrapper for transducers that may want to signal that the
 * reduction is finished.
 *
 * @see state_wrapper
 * @see state_traits::reduced
 */
template <typename T>
using maybe_reduced = state_wrapper<maybe_reduced_tag, T, bool>;

inline bool state_wrapper_data_is_reduced(maybe_reduced_tag, bool is_reduced)
{
  return is_reduced;
}

/*!
 * Wraps @a x in a `maybe_reduced`, where `is_reduced` contains
 * whether the reduction should actually finish.
 */
template <typename T>
auto reduced_if(T&& x, bool is_reduced)
  -> maybe_reduced<estd::decay_t<T> >
{
  return maybe_reduced<estd::decay_t<T> > {
    std::forward<T>(x),
    is_reduced
  };
}

/*!
 * Wraps @a x such that the reduction should finish.
 */
template <typename T>
auto reduced(T&& x)
  -> ABL_DECLTYPE_RETURN(
    reduced_if(std::forward<T>(x), true))

/*!
 * Wraps @a x such that the reduction should continue.
 */
template <typename T>
auto not_reduced(T&& x)
  -> ABL_DECLTYPE_RETURN(
    reduced_if(std::forward<T>(x), false))

} // namespace xform
} // namespace atria
