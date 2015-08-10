// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/state_traits.hpp>
#include <tuple>

namespace atria {
namespace xform {

/*!
 * Default tag for `state_wrapper`.
 * @see state_wrapper
 */
struct no_tag {};

/*!
 * A decorator for the accumulator of a reduction.
 *
 * A transducer must not make any assumptions about the accumulator of
 * the process it is helping to reduce.  However, a *stateful
 * transducer* may use a `state_wrapper` to attach extra data to the
 * accumulator such that the reducing function object itself can be state-less.
 *
 * A state wrapper has the following template arguments:
 *
 * @tparam TagT is as tag type used to identify the transducer that is
 *        attaching the state.  This can useful to specialize the
 *        `state_traits` for a concrete state wrapper.
 *
 * @tparam StateT is the accumulator that is to be wrapped and of which
 *        we shall make no assumptions.
 *
 * @tparam DataT is the additional data that the transducer wants to
 *        attach to represent its own state.
 *
 * For an example of a stateful reducing function, @see take
 *
 * @see wrap_state
 * @see state_traits
 */
template <typename TagT   = no_tag,
          typename StateT = void,
          typename DataT  = void>
struct state_wrapper : std::tuple<StateT, DataT>
{
  using tag = TagT;
  using base_t = std::tuple<StateT, DataT>;

  state_wrapper(const state_wrapper&) = default;
  state_wrapper(state_wrapper&&) = default;
  state_wrapper& operator=(const state_wrapper&) = default;
  state_wrapper& operator=(state_wrapper&&) = default;

  template <typename T, typename U>
  state_wrapper(T&& st, U&& data)
    : base_t(std::forward<T>(st), std::forward<U>(data))
  {}
};

/*!
 * Metafunction returning whether `StateT` is a, or reference to, a
 * `state_wrapper` instantiation.
 */
template <typename StateT, typename DecayedT = estd::decay_t<StateT> >
struct is_state_wrapper
  : std::false_type {};

template <typename _, typename T, typename S, typename D>
struct is_state_wrapper<_, state_wrapper<T, S, D> >
  : std::true_type {};

/*!
 * Given a tag `TagT` and a state `next` and associated `data`,
 * returns a `state_wrapper` instance.
 *
 * @see state_wrapper
 */
template <typename TagT=void, typename StateT, typename DataT>
auto wrap_state(StateT&& next, DataT&& data)
  -> state_wrapper<TagT,
                   estd::decay_t<StateT>,
                   estd::decay_t<DataT> >
{
  return state_wrapper<TagT, estd::decay_t<StateT>, estd::decay_t<DataT> > {
    std::forward<StateT>(next),
    std::forward<DataT>(data)
  };
}

/*!
 * Utility function for easy overloading of `state_traits::complete`
 * for state wrappers with a specific tag.
 *
 * @see state_wrapper
 * @see state_traits::complete
 */
template <typename TagT, typename T>
auto state_wrapper_complete(TagT, T&& s)
  -> ABL_DECLTYPE_RETURN(
    state_complete(state_unwrap(std::forward<T>(s))))

/*!
 * Utility function for easy overloading of `state_traits::unwrap`
 * for state wrappers with a specific tag.
 *
 * @see state_wrapper
 * @see state_traits::unwrap
 */
template <typename TagT, typename T>
auto state_wrapper_unwrap(TagT, T&& s)
  -> ABL_DECLTYPE_RETURN(
    std::get<0>(std::forward<T>(s)))

/*!
 * Utility function for easy overloading of `state_traits::data`
 * for state wrappers with a specific tag.
 *
 * @see state_wrapper
 * @see state_traits::data
 */
template <typename TagT, typename T, typename D>
auto state_wrapper_data(TagT tag, T&& s, D&&)
  -> ABL_DECLTYPE_RETURN(
    state_wrapper_data(tag, std::forward<T>(s)))

template <typename T>
auto state_wrapper_data(T&& s)
  -> ABL_DECLTYPE_RETURN(
    state_wrapper_data(typename estd::decay_t<T>::tag{}, std::forward<T>(s)))

template <typename TagT, typename T>
auto state_wrapper_data(TagT, T&& s)
  -> ABL_DECLTYPE_RETURN(
    std::get<1>(std::forward<T>(s)))

/*!
 * Utility function that returns whether the `DataT` associated with a
 * state wrapper with tag `TagT` is reduced -- i.e. idempotent.
 * Can be overloaded custom tags.
 *
 * @see state_traits::reduced
 */
template <typename TagT, typename DataT>
bool state_wrapper_data_is_reduced(TagT, DataT&&)
{
  return false;
}

/*!
 * Utility function for easy overloading of `state_traits::is_reduced`
 * for state wrappers with a specific tag.  Most of the time you may
 * want to overload `state_wrapper_is_reduced` instead.
 *
 * @see state_wrapper_data_is_reduced
 * @see state_wrapper
 * @see state_traits::is_reduced
 */
template <typename TagT, typename T>
bool state_wrapper_is_reduced(TagT tag, T&& s)
{
  return state_wrapper_data_is_reduced(
           tag, state_wrapper_data(tag, std::forward<T>(s)))
      || state_is_reduced(state_unwrap(std::forward<T>(s)));
}

/*!
 * State traits specialization for `state_wrapper`.  Just forwards to
 * the `state_wrapper_*` methods, that are easier to specialize for a
 * given tag.
 *
 * @see state_wrapper_complete
 * @see state_wrapper_is_reduced
 * @see state_wrapper_unwrap
 * @see state_wrapper_data
 * @see state_wrapper
 */
template <typename TagT, typename StateT, typename DataT>
struct state_traits<state_wrapper<TagT, StateT, DataT> >
{
  template <typename T>
  static auto complete(T&& s)
    -> ABL_DECLTYPE_RETURN(
      state_wrapper_complete(TagT{}, std::forward<T>(s)))

  template <typename T>
  static auto is_reduced(T&& s)
    -> ABL_DECLTYPE_RETURN(
      state_wrapper_is_reduced(TagT{}, std::forward<T>(s)))

  template <typename T, typename D>
  static auto data(T&& s, D&& d)
    -> ABL_DECLTYPE_RETURN(
      state_wrapper_data(TagT{}, std::forward<T>(s), std::forward<D>(d)))

  template <typename T>
  static auto unwrap(T&& s)
    -> ABL_DECLTYPE_RETURN(
      state_wrapper_unwrap(TagT{}, std::forward<T>(s)))
};

} // namespace xform
} // namespace atria
