// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {

//!
// Interface for a type specializing the `State` concept.
//
// A `State` is the first parameter of a reducer, also known as the
// accumulator.  Every type is a model of `State`, with the following
// default implementation. However, one might want to specialize the
// state it for a particular accumulator type, such that transducers
// can operate with it.  A transducer should not make assumptions
// about the state it receives, instead, it can only wrap it using
// `wrap_state` to attach additional data.
//
// For an example of a stateful reducer, @see take
//
// @see wrap_state
//
template <typename StateT>
struct state_traits
{
  //!
  // Returns whether the value is idempotent, and thus, the reduction
  // can finish.
  //
  template <typename T>
  static auto is_reduced(T&&) -> bool
    { return false; }

  //!
  // Returns the associated from the current state.  If the state
  // contains no associated data, the `default_data` will be returned.
  //
  template <typename T, typename D>
  static auto data(T&&, D&& default_data) -> D&&
    { return std::forward<D>(default_data); }

  //!
  // Unwraps all the layers of state wrappers returning the deepmost
  template <typename T>
  static auto complete(T&& state) -> T&&
    { return std::forward<T>(state); }

  //!
  // Unwraps this layers of state wrappers, returning the nested
  // state for the next reducer.
  //
  template <typename T>
  static auto unwrap(T&& state) -> T&&
    { return std::forward<T>(state); }
};

template <typename T>
using state_traits_t = state_traits<estd::decay_t<T> >;

//!
// Convenience function for calling `state_traits::complete`
//
template <typename T>
auto state_complete(T&& s)
  -> decltype(state_traits_t<T>::complete(std::forward<T>(s)))
{
  return state_traits_t<T>::complete(std::forward<T>(s));
}

//!
// Convenience function for calling `state_traits::is_reduced`
//
template <typename T>
auto state_is_reduced(T&& s) -> bool
{
  return state_traits_t<T>::is_reduced(std::forward<T>(s));
}

//!
// Convenience function for calling `state_traits::data`
//
template <typename T, typename D>
auto state_data(T&& s, D&& d)
  -> decltype(state_traits_t<T>::data(std::forward<T>(s),
                                      std::forward<D>(d)))
{
  return state_traits_t<T>::data(std::forward<T>(s),
                                 std::forward<D>(d));
}

//!
// Convenience function for calling `state_traits::unwrap`
//
template <typename T>
auto state_unwrap(T&& s)
  -> decltype(state_traits_t<T>::unwrap(std::forward<T>(s)))
{
  return state_traits_t<T>::unwrap(std::forward<T>(s));
}

//!
// A decorator for the accumulator of a reduction.
//
// A transducer must not make any assumptions about the accumulator of
// the process it is helping to reduce.  However, a *stateful
// transducer* may use a `state_wrapper` to attach extra data to the
// accumulator such that the reducer object itself can be state-less.
//
// A state wrapper has the following template arguments:
//
// @param TagT is as tag type used to identify the transducer that is
//        attaching the state.  This can useful to specialize the
//        `state_traits` for a concrete state wrapper.
//
// @param StateT is the accumulator that is to be wrapped and of which
//        we shall make no assumptions.
//
// @param DataT is the additional data that the transducer wants to
//        attach to represent its own state.
//
// For an example of a stateful reducer, @see take
//
// @see wrap_state
// @see state_traits
//
template <typename TagT   = void,
          typename StateT = void,
          typename DataT  = void>
struct state_wrapper : std::tuple<StateT, DataT>
{
  using tag = TagT;

  using base_t = std::tuple<StateT, DataT>;
  using base_t::base_t;

  template <typename T>
  explicit state_wrapper(
    T&& st,
    estd::enable_if_t<
      !std::is_base_of<state_wrapper, estd::decay_t<T> >::value
    >* = 0)
    : base_t(std::forward<T>(st), DataT{})
  {}
};

//!
// Metafunction returning whether `StateT` is a, or reference to, a
// `state_wrapper` instantiation.
//
template <typename StateT, typename DecayedT = estd::decay_t<StateT> >
struct is_state_wrapper
  : std::false_type {};

template <typename _, typename T, typename S, typename D>
struct is_state_wrapper<_, state_wrapper<T, S, D> >
  : std::true_type {};

//!
// Given a tag `TagT` and a state `next` and associated `data`,
// returns a `state_wrapper` instance.
//
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

//!
// Utility function that returns whether the `DataT` associated with a
// state wrapper with tag `TagT` is reduced -- i.e. idempotent.
//
// @see state_traits::reduced
//
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
    -> decltype(state_complete(state_unwrap(std::forward<T>(s))))
  {
    return state_complete(state_unwrap(std::forward<T>(s)));
  }

  template <typename T>
  static auto is_reduced(T&& s) -> bool
  {
    using tag_t = typename estd::decay_t<T>::tag;
    return state_data_is_reduced(tag_t{}, std::get<1>(std::forward<T>(s)))
        || state_is_reduced(std::get<0>(std::forward<T>(s)));
  }

  template <typename T, typename D>
  static auto data(T&& s, D&& d)
    -> decltype(std::get<1>(std::forward<T>(s)))
  {
    return std::get<1>(std::forward<T>(s));
  }

  template <typename T>
  static auto unwrap(T&& s)
    -> decltype(std::get<0>(std::forward<T>(s)))
  {
    return std::get<0>(std::forward<T>(s));
  }
};

} // namespace xform
} // namespace atria
