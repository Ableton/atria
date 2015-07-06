// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/state_traits.hpp>
#include <tuple>

namespace atria {
namespace xform {

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
template <typename TagT   = void,
          typename StateT = void,
          typename DataT  = void>
struct state_wrapper : std::tuple<StateT, DataT>
{
  using tag = TagT;
  using base_t = std::tuple<StateT, DataT>;

  template <typename T, typename U>
  state_wrapper(T&& st, U&& data)
    : base_t(std::forward<T>(st), std::forward<U>(data))
  {}

  template <typename T>
  explicit state_wrapper(
    T&& st,
    estd::enable_if_t<
      !std::is_base_of<state_wrapper, estd::decay_t<T> >::value
    >* = 0)
    : base_t(std::forward<T>(st), DataT{})
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
 * Utility function that returns whether the `DataT` associated with a
 * state wrapper with tag `TagT` is reduced -- i.e. idempotent.
 *
 * @see state_traits::reduced
 */
template <typename TagT, typename DataT>
bool state_data_is_reduced(TagT, DataT&&)
{
  return false;
}

template <typename TagT, typename StateT, typename DataT>
struct state_traits<state_wrapper<TagT, StateT, DataT> >
{
  template <typename T>
  static auto complete(T&& s)
    -> ABL_AUTO_RETURN(
      state_complete(state_unwrap(std::forward<T>(s))))

  template <typename T>
  static auto is_reduced(T&& s) -> bool
  {
    using tag_t = typename estd::decay_t<T>::tag;
    return state_data_is_reduced(tag_t{}, std::get<1>(std::forward<T>(s)))
        || state_is_reduced(std::get<0>(std::forward<T>(s)));
  }

  template <typename T, typename D>
  static auto data(T&& s, D&&)
    -> ABL_AUTO_RETURN(
      std::get<1>(std::forward<T>(s)))

  template <typename T>
  static auto unwrap(T&& s)
    -> ABL_AUTO_RETURN(
      std::get<0>(std::forward<T>(s)))
};

} // namespace xform
} // namespace atria
