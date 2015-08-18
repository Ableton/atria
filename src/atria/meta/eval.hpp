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

#include <boost/preprocessor/seq/for_each_i.hpp>

namespace atria {
namespace meta {

/*!
 * Alias to access `typename T::type`
 */
template <typename T>
using eval_t = typename T::type;

/*!
 * Macro to define an evaluated version of a metafunction with `_t`
 * suffix, in the style of the C++14 standard library.
 */
#define ABL_METAFUNCTION_T(name__)                              \
  template <typename... Ts>                                     \
  using name__ ## _t = ::atria::meta::eval_t<name__ <Ts...> >   \
  /**/

#if ABL_CXX14
/*!
 * Alias to access `T::type::value`
 */
template <typename T>
constexpr auto eval_v = T::type::value;

/*!
 * Macro to define an evaluated version of a value-metafunction with
 * `_v` suffix, in the style of the C++14 standard library.
 */
#define ABL_METAFUNCTION_V(name__)                                      \
  template <typename... Ts>                                             \
  constexpr auto name__ ## _v = ::atria::meta::eval_v<name__ <Ts...> >  \
  /**/
#else
#define ABL_METAFUNCTION_V(name__)
#endif // ABL_CXX14

} // namespace meta
} // namespace atria
