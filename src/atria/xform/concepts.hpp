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

#include <atria/prelude/constantly.hpp>
#include <atria/meta/concept.hpp>
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {

/*!
 * Concept for a type that can be used as a `state` of a reducing
 * function.  By default, every type is a model of it.  However, one
 * might use this concept to check that a specialization of
 * `state_traits` is still valid.
 */
ABL_CONCEPT_SPEC(State)
{
  struct any_t
  {
    any_t();
    template <typename T> any_t(T);
  };

  template <typename T>
  auto requires_(T&& t)
    -> decltype(
      meta::expressions(
        state_unwrap(t),
        state_complete(t),
        bool(state_is_reduced(t)),
        any_t(state_data(t, constantly(any_t{}))),
        meta::require_any<
          decltype(state_unwrap(t)),
          std::is_same<T, boost::mpl::_>,
          meta::models_<State_spec, boost::mpl::_> >()));
};

/*!
 * Concept for a function that can be used with `reduce` for a
 * specific state and inputs.
 */
ABL_CONCEPT_SPEC(Reducing_function)
{
  template <typename R, typename S, typename... Is>
  auto requires_(R&& r, S&& s, Is&&... is)
    -> decltype(
      meta::expressions(
        r(s, is...),
        r(r(s, is...), is...),
        meta::require<(
          std::is_same<
            decltype(r(s, is...)),
            decltype(r(r(s, is...), is...))>())>(),
        meta::require<(
          State<decltype(r(s, is...))>())>(),
        meta::require<(
          State<decltype(r(r(s, is...), is...))>())>()));
};

namespace detail {

template <typename R, typename S, typename I>
struct is_reducing_function
  : std::integral_constant<bool, Reducing_function<R, S, I>()>
{};

template <typename R, typename S, typename... Is>
struct is_reducing_function<R, S, meta::pack<Is...> >
  : std::integral_constant<bool, Reducing_function<R, S, Is...>()>
{};

template <typename I>
struct decl_reducing_function
{
  template <typename S>
  auto operator() (S&&, I) -> S&&;
};

template <typename... Is>
struct decl_reducing_function<meta::pack<Is...> >
{
  template <typename S>
  auto operator() (S&&, Is...) -> S&&;
};

} // namespace detail

/*!
 * Concept for a `transducer`, this is, a function that takes a
 * *reducing function* as an argument, and decorates it returning a new
 * *reducing function*.
 *
 * The second and third argument use the same rules the arguments to
 * `transducer`.
 *
 * @see `transducer`
 */
ABL_CONCEPT_SPEC(Transducer)
{
  struct foo_t {};

  template <typename T>
  using rf_t = detail::decl_reducing_function<T>;

  template <typename T, typename InputT, typename OutputT>
  auto requires_(T&& t, InputT, OutputT)
    -> decltype(
      meta::expressions(
        t(rf_t<OutputT>{}),
        meta::require<(
          detail::is_reducing_function<
            decltype(t(rf_t<OutputT>{})),
            foo_t,
            InputT>())>()));

  template <typename T, typename InputT>
  auto requires_(T&& t, InputT&& i)
    -> decltype(requires_(t, i, i));
};

/*!
 * Concept for a transducer that can be applied over any arguments.
 */
ABL_CONCEPT_SPEC(Transparent_transducer)
{
  struct foo_t {};
  struct bar_t {};
  struct baz_t {};

  template <typename T>
  auto requires_(T&& t)
    -> decltype(
      meta::expressions(
        meta::require<(
          Transducer<T, foo_t>())>(),
        meta::require<(
          Transducer<T, meta::pack<bar_t, foo_t> >())>(),
        meta::require<(
          Transducer<T, meta::pack<baz_t, bar_t, foo_t> >())>()));
};

} // namespace xform
} // namespace atria
