// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>

namespace atria {
namespace xform {

namespace detail {

struct take_rf_gen
{
  struct tag {};

  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT total;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        wrap_state<tag>(
          step(state_unwrap(std::forward<StateT>(s)),
               std::forward<InputTs>(is)...),
          state_data(std::forward<StateT>(s),
                     constantly(total)) - 1))
  };

  template <typename T>
  friend bool state_wrapper_data_is_reduced(tag, T&& n)
  {
    return std::forward<T>(n) == 0;
  }
};

} // namespace detail

template <typename T>
using take_t = transducer_impl<detail::take_rf_gen, T>;

/*!
 * Similar to clojure.core/take$1
 */
template <typename IntegralT>
auto take(IntegralT&& n)
  -> take_t<estd::decay_t<IntegralT> >
{
  return take_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(n) };
}

namespace impure {

namespace detail {

struct take_rf_gen
{
  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT total;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s), std::forward<InputTs>(is)...))
    {
      if (total == 0)
        abort_reduce(std::forward<StateT>(s));
      --total;
      return step(std::forward<StateT>(s), std::forward<InputTs>(is)...);
    }
  };
};

} // namespace detail

template <typename T>
using take_t = transducer_impl<detail::take_rf_gen, T>;

template <typename IntegralT>
auto take(IntegralT&& n)
  -> take_t<estd::decay_t<IntegralT> >
{
  return take_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(n) };
}

} // namespace impure

} // namespace xform
} // namespace atria
