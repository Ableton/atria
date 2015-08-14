// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>

namespace atria {
namespace xform {
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
