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

struct enumerate_rf_gen
{
  template <typename ReducingFnT, typename CountT>
  struct apply
  {
    ReducingFnT step;
    CountT count;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
          step(std::forward<StateT>(s),
               count++,
               std::forward<InputTs>(is)...))
  };
};

} // namespace detail

template <typename T>
using enumerate_t = transducer_impl<detail::enumerate_rf_gen, T>;

template <typename IntegralT>
constexpr auto enumerate_from(IntegralT&& init)
  -> enumerate_t<estd::decay_t<IntegralT> >
{
  return enumerate_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(init) };
}

extern const enumerate_t<std::size_t> enumerate;

} // namespace impure
} // namespace xform
} // namespace atria
