// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

namespace detail {

struct repeat_rf_gen
{
  template <typename ReducingFnT,
            typename ValueT>
  struct apply
  {
    ReducingFnT step;
    ValueT value;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        step(std::forward<StateT>(s), std::forward<InputTs>(is)..., value))
  };
};

} // namespace detail

template <typename T>
using repeat_t = transducer_impl<detail::repeat_rf_gen, T>;

/*!
 * Generator transducer produces the values passed as parameter
 * infinitely.
 */
template <typename ValueT>
constexpr auto repeat(ValueT&& r)
  -> repeat_t<estd::decay_t<ValueT> >
{
  return repeat_t<estd::decay_t<ValueT> > {
    std::forward<ValueT>(r) };
}

template <typename ValueT, typename ...ValueTs>
constexpr auto repeat(ValueT&& r, ValueTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(repeat(std::forward<ValueT>(r)),
         repeat(std::forward<ValueTs>(rs))...))

/*!
 * Generator transducer produces the values passed as parameter
 * up to `n` times.
 */
template <typename IntegralT, typename ...ValueTs>
constexpr auto repeatn(IntegralT&& n, ValueTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(repeat(std::forward<ValueTs>(rs)...),
         take(std::forward<IntegralT>(n))))

} // namespace xform
} // namespace atria
