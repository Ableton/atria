// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto enumerate_from = [](auto initial) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      auto count = state_data(ABL_FORWARD(s), constantly(initial));
      return wrap_state(
        step(state_unwrap(ABL_FORWARD(s)),
             std::move(count),
             ABL_FORWARD(is)...),
        decltype(initial)(std::move(count) + 1));
    };
  };
};

auto enumerate = enumerate_from(std::size_t{});

#else // ABL_CXX14

namespace detail {

struct enumerate_rf_gen
{
  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT initial;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), initial, is...), initial))
    {
      auto next  = state_data(std::forward<StateT>(s), constantly(initial));
      auto count = next++;
      return wrap_state(
        step(state_unwrap(std::forward<StateT>(s)),
             std::move(count),
             std::forward<InputTs>(is)...),
        std::move(next));
    }
  };
};

} // namespace detail

template <typename T>
using enumerate_t = transducer_impl<detail::enumerate_rf_gen, T>;

/*!
 * Transducer that given a sequence:
 *
 *   $$x_0, x_1, ..., x_n$$
 *
 * produces a sequence
 *
 *   $$(init, x_0), (init+1, x_1), ..., (init+n, x_n)$$
 *
 * It is inspired by Python's `enumerate` generator.
 */
template <typename IntegralT>
constexpr auto enumerate_from(IntegralT&& init)
  -> enumerate_t<estd::decay_t<IntegralT> >
{
  return enumerate_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(init) };
}

/*!
 * Equivalent to `enumerate_from(std::size_t{})`.
 * @todo Should be `constexpr` in C++14
 */
extern const enumerate_t<std::size_t> enumerate;

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
