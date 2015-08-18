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

#include <atria/estd/type_traits.hpp>
#include <utility>

namespace atria {
namespace funken {

namespace detail {

/*!
 * Provides access to the underlying signals of different
 * entities. This encapsulates acess to the implementation of
 * signal-based objects: don't make access to signals public, instead
 * friend this class.
 */
class access
{
public:

  /*!
   * Returns a smart pointer to the underlying root signal or signals
   * of an object, if exist.
   */
  template<typename T>
  static auto roots(T&& object)
    -> ABL_DECLTYPE_RETURN(
      std::forward<T>(object).roots())

  /*!
   * Returns a pointer to th underlying signal of an object, if
   * exists.
   */
  template<typename T>
  static auto signal(T&& object)
    -> ABL_DECLTYPE_RETURN(
      std::forward<T>(object).signal())

  /*!
   * Returns a a optional boost.signal to the specific watchers of
   * the underlying signal of an object.
   */
  template<typename T>
  static auto watchers(T&& object)
    -> ABL_DECLTYPE_RETURN(
      std::forward<T>(object).watchers())
};

/*!
 * Returns the signal type for an object
 */
template <typename ObjectT>
struct signal_type
{
  using type =
    estd::decay_t<
      typename estd::decay_t<decltype(
        access::signal(std::declval<ObjectT>())
      )>::element_type
    >;
};

template <typename ObjectT>
using signal_type_t = typename signal_type<ObjectT>::type;

} // namespace detail

} // namespace funken
} // namespace atria
