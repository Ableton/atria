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
#include <atria/estd/utility.hpp>
#include <atria/meta/utils.hpp>

namespace atria {
namespace xform {

/*!
 * Interface for a type specializing the `State` concept.
 *
 * A `State` is the first parameter of a reducing function, also known as the
 * accumulator.  Every type is a model of `State`, with the following
 * default implementation. However, one might want to specialize the
 * state it for a particular accumulator type, such that transducers
 * can operate with it.  A transducer should not make assumptions
 * about the state it receives, instead, it can only wrap it using
 * `wrap_state` to attach additional data.
 *
 * For an example of a stateful reducing function, see `take`.
 *
 * @see wrap_state
 * @see take
 */
template <typename StateT>
struct state_traits
{
  /*!
   * Returns whether the value is idempotent, and thus, the reduction
   * can finish.
   */
  template <typename T>
  static auto is_reduced(T&&) -> bool
    { return false; }

  /*!
   * Returns the associated from the current state.  If the state
   * contains no associated data, the `default_data` will be returned.
   */
  template <typename T, typename D>
  static auto data(T&&, D&& d)
    -> ABL_DECLTYPE_RETURN(std::forward<D>(d)())

  /*!
   * Unwraps all the layers of state wrappers returning the deepmost
   */
  template <typename T>
  static auto complete(T&& state)
    -> ABL_DECLTYPE_RETURN(std::forward<T>(state))

  /*!
   * Unwraps this layers of state wrappers, returning the nested
   * state for the next reducing function.
   */
  template <typename T>
  static auto unwrap(T&& state)
    -> ABL_DECLTYPE_RETURN(std::forward<T>(state))

  /*!
   * Unwraps all layers of state wrappers, returning the most nested
   * state for the innermost reducing function.
   */
  template <typename T>
  static auto unwrap_all(T&& state)
    -> ABL_DECLTYPE_RETURN(std::forward<T>(state))

  /*!
   * Copies all layers of state wrappers but replaces the innermost
   * state with `substate`.
   */
  template <typename T, typename U>
  static auto rewrap(T&&, U&& x)
    -> ABL_DECLTYPE_RETURN(std::forward<U>(x))
};

template <typename T>
using state_traits_t = state_traits<estd::decay_t<T> >;

/*!
 * Convenience function for calling `state_traits::complete`
 */
template <typename T>
auto state_complete(T&& s)
  -> ABL_DECLTYPE_RETURN(
    state_traits_t<T>::complete(std::forward<T>(s)))

/*!
 * Convenience function for calling `state_traits::is_reduced`
 */
template <typename T>
auto state_is_reduced(T&& s) -> bool
{
  return state_traits_t<T>::is_reduced(std::forward<T>(s));
}

/*!
 * Convenience function for calling `state_traits::data`
 */
template <typename T, typename D>
auto state_data(T&& s, D&& d)
  -> ABL_DECLTYPE_RETURN(
    state_traits_t<T>::data(std::forward<T>(s),
                            std::forward<D>(d)))

/*!
 * Convenience function for calling `state_traits::unwrap`
 */
template <typename T>
auto state_unwrap(T&& s)
  -> ABL_DECLTYPE_RETURN(
    state_traits_t<T>::unwrap(std::forward<T>(s)))

/*!
 * Convenience function for calling `state_traits::unwrap_all`
 */
template <typename T>
auto state_unwrap_all(T&& s)
  -> ABL_DECLTYPE_RETURN(
    state_traits_t<T>::unwrap_all(std::forward<T>(s)))

/*!
 * Convenience function for calling `state_traits::unwrap_all`
 */
template <typename T, typename U>
auto state_rewrap(T&& s, U&& x)
  -> ABL_DECLTYPE_RETURN(
    state_traits_t<T>::rewrap(std::forward<T>(s), std::forward<U>(x)))

} // namespace xform
} // namespace atria
