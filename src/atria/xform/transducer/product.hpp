// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/detail/empty_transducer_error.hpp>
#include <atria/xform/reduce_nested.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

namespace detail {

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT,
          typename... ValueTs>
auto reduce_nested_non_empty_product(ReducingFnT&& step,
                                     StateT&& initial,
                                     InputRangeT&& range,
                                     ValueTs&& ...values)
  -> estd::decay_t<decltype(step(initial, values..., *std::begin(range)))>
{
  auto first = std::begin(range);
  auto last  = std::end(range);
  auto state = step(std::forward<StateT>(initial), values..., *first);
  for (++first; !state_is_reduced(state) && first != last; ++first) {
    auto new_state = step(std::move(state), values..., *first);
    state = std::move(new_state);
  }
  return state;
}

struct product_rf_gen
{
  template <typename ReducingFnT,
            typename InputRangeT>
  struct apply
  {
    ReducingFnT step;
    InputRangeT range;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        reduce_nested_non_empty_product(
          step,
          std::forward<StateT>(s),
          range,
          std::forward<InputTs>(is)...))
  };
};

} // namespace detail

template <typename T>
using product_t = transducer_impl<detail::product_rf_gen, T>;

/*!
 * Transducer combines every element that passes by with every element
 * in the sequence that it takes as arguemnt.
 * Like itertools.product, from Python.
 */
template <typename InputRangeT>
constexpr auto product(InputRangeT&& r)
  -> product_t<estd::decay_t<InputRangeT> >
{
  return product_t<estd::decay_t<InputRangeT> > {
    detail::check_non_empty(std::forward<InputRangeT>(r)) };
}

template <typename InputRangeT, typename ...InputRangeTs>
constexpr auto product(InputRangeT&& r, InputRangeTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(product(std::forward<InputRangeT>(r)),
         product(std::forward<InputRangeTs>(rs))...))

} // namespace xform
} // namespace atria
