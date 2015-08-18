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

#include <atria/xform/state_traits.hpp>
#include <atria/variant/match_eggs.hpp>
#include <atria/meta/common_type.hpp>
#include <atria/estd/utility.hpp>
#include <functional>

namespace atria {
namespace xform {

/*!
 * Type-safe union type that can hold values of both @a SkippedT and
 * @a CalledT types.
 *
 * @see skip
 */
template <typename SkippedT, typename CalledT>
struct skip_state : eggs::variant<SkippedT, CalledT>
{
  using skipped_t = SkippedT;
  using called_t  = CalledT;

  using variant_types = meta::pack<skipped_t, called_t>;

  using base_t = eggs::variant<SkippedT, CalledT>;
  using base_t::base_t;
};

} // namespace xform
} // namespace atria

namespace atria {
namespace xform {

template <typename T>
struct is_skip_state
  : std::false_type {};

template <typename SkippedT, typename CalledT>
struct is_skip_state<skip_state<SkippedT, CalledT> >
  : std::true_type {};

namespace detail {

struct state_is_reduced_t
{
  template <typename T>
  auto operator() (T&& s)
    -> ABL_DECLTYPE_RETURN(
      state_is_reduced(std::forward<T>(s)))
};

struct state_complete_t
{
  template <typename T>
  auto operator() (T&& s)
    -> ABL_DECLTYPE_RETURN(
      state_complete(std::forward<T>(s)))
};

} // namespace detail

template <typename SkippedT, typename CalledT>
struct state_traits<skip_state<SkippedT, CalledT> >
{
  template <typename T>
  static auto is_reduced(T&& s)
    -> ABL_DECLTYPE_RETURN(
      variant::match(
        std::forward<T>(s),
        detail::state_is_reduced_t{}))

  template <typename T>
  static auto complete(T&& s)
    -> ABL_DECLTYPE_RETURN(
      variant::match(
        std::forward<T>(s),
        variant::otherwise<SkippedT>(detail::state_complete_t{})))

  // In practice, this method does not make sense for this type.  It
  // is unwrapped manually by @a call
  template <typename T, typename D>
  static auto data(T&&, D&& d)
    -> ABL_DECLTYPE_RETURN(
      std::forward<D>(d)())

  // In practice, this method does not make sense for this type.  It
  // is unwrapped manually by @a call
  template <typename T>
  static auto unwrap(T&& s)
    -> ABL_DECLTYPE_RETURN(
      std::forward<T>(s))
};

namespace detail
{

template <typename ReducingFnT, typename StateT, typename... InputTs>
struct skip_result_impl
{
  using skipped_t = StateT;
  using called_t  = estd::result_of_t<ReducingFnT(StateT, InputTs...)>;

  using common_type_t = meta::common_type_t<skipped_t, called_t>;
  using error_t = meta::could_not_find_common_type<skipped_t, called_t>;

  using type = estd::conditional_t<
    !std::is_same<common_type_t, error_t>{},
      common_type_t,
      skip_state<estd::decay_t<skipped_t>,
                 estd::decay_t<called_t> > >;
};

} // namespace detail

/*!
 * Metafunction that returns a type that can hold both values of type
 *   `skipped_t = StateT`
 * and
 *   `wrapped_t = declval<ReducingFnT>(declval<StateT>(),
 *                                     declval<InputTs>()...)`
 *
 * The result is:
 *
 *   - If a `std::common_type<skipped_t, wrapped_t>` exists between
 *     the two types, it returns this type.  For example, if one of
 *     these is a `any_state` because is used in a type erased
 *     transducer, `any_state` will be the result.
 *
 *   - Otherwise, it returns `skip_state<skipped_t, wrapped_t>`, which
 *     is essentially a type-safe union of these two types.
 *
 * @see skip
 */
template <typename ReducingFnT, typename StateT, typename... InputTs>
struct skip_result
  : boost::mpl::eval_if<
     is_skip_state<estd::decay_t<StateT> >,
       boost::mpl::identity<estd::decay_t<StateT> >,
       detail::skip_result_impl<ReducingFnT, StateT, InputTs...> >
{};

template <typename ReducingFnT, typename StateT, typename... InputTs>
using skip_result_t = typename skip_result<
  ReducingFnT, StateT, InputTs...>::type;

/*!
 * Skip calling the next reducing function in a transducer.  Returns
 * the @a state parameter, potentially wrapped in a value convertible
 * to/from whatever @a call would return for similar parameters.
 *
 * A transducer might or might not call the next reducing function in
 * the chain.  One good example is @a filter, where if the predicate
 * passes, it calls the next reducing function, otherwise it just
 * returns the current state of the reduction.  However, this poses
 * the question: what should be the return type of such a transducer?
 * The next reducing function might wrap the state in a @a
 * state_wrapper to attach its own state to it.  However, we don't
 * know at this point what how to create such a wrapped value.  This
 * method, and @a call, take care of wrapping the state in a type that
 * can hold values of both the current state, and the state that
 * would be returned by the next reducing function. The metafunction
 * @a skip_result defines such a type.
 *
 * @see call
 * @see skip_result_t
 * @see filter
 * @see wrap_state
 */
template <typename ReducingFnT, typename StateT, typename... InputTs>
auto skip(ReducingFnT&&, StateT&& state, InputTs&& ...)
  -> skip_result_t<ReducingFnT, StateT, InputTs...>
{
  return std::forward<StateT>(state);
}

template <typename StateT>
auto skip(StateT&& state)
  -> StateT&&
{
  return std::forward<StateT>(state);
}

namespace detail {

template <typename ReducingFnT, typename... InputTs>
struct bind_forward_reducing_function
{
  ReducingFnT&& fn;
  std::tuple<InputTs&&...> ins;

  template <std::size_t... Indices, typename StateT>
  auto impl(estd::index_sequence<Indices...>, StateT&& st)
    -> ABL_DECLTYPE_RETURN(
      std::forward<ReducingFnT>(fn)(
        std::forward<StateT>(st),
        std::forward<typename std::tuple_element<Indices, decltype(ins)>::type>(
          std::get<Indices>(ins))...))

  template <typename StateT>
  auto operator() (StateT&& st)
    -> ABL_DECLTYPE_RETURN(
      impl(estd::make_index_sequence<sizeof...(InputTs)>{},
           std::forward<StateT>(st)))
};

} // namespace detail

/*!
 * Call the next reducing function in a transducer that could
 * otherwise skip calling the next reducing function.  Returns the
 * result of calling `step(state, ins...)` wrapped in a type that can
 * also hold plain `state` values.  If @a state is wrapped in such a
 * type, it unwraps it before passing it.
 *
 * @see skip
 */
template <typename ReducingFnT, typename StateT, typename... InputTs>
auto call(ReducingFnT&& step, StateT&& state, InputTs&& ...ins)
  -> estd::enable_if_t<
    is_skip_state<estd::decay_t<StateT> >{},
    estd::decay_t<StateT> >
{
  return variant::match(
    std::forward<StateT>(state),
    detail::bind_forward_reducing_function<ReducingFnT, InputTs...> {
      std::forward<ReducingFnT>(step),
        std::forward_as_tuple<InputTs...>(ins...)
      });
}

template <typename ReducingFnT, typename StateT, typename... InputTs>
auto call(ReducingFnT&& step, StateT&& state, InputTs&& ...ins)
  -> estd::enable_if_t<
    !is_skip_state<estd::decay_t<StateT> >{},
    skip_result_t<ReducingFnT, StateT, InputTs...> >
{
  return std::forward<ReducingFnT>(step)(
    std::forward<StateT>(state),
    std::forward<InputTs>(ins)...);
}

} // namespace xform
} // namespace atria
