
// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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
