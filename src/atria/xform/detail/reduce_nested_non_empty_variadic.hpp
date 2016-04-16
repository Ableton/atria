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

#include <atria/xform/detail/tuple_utils.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/estd/utility.hpp>
#include <atria/meta/copy_traits.hpp>
#include <atria/meta/pack.hpp>
#include <iterator>
#include <tuple>

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputTs,
          typename ...InputRangeTs>
auto reduce_nested_non_empty_variadic_impl(estd::index_sequence<Indices...>,
                                           meta::pack<InputTs...>,
                                           ReducingFnT&& step,
                                           StateT&& initial,
                                           InputRangeTs&& ...ranges)
  -> estd::decay_t<decltype(step(initial, *std::begin(ranges)...))>
{
  auto firsts = std::make_tuple(std::begin(ranges)...);
  auto lasts  = std::make_tuple(std::end(ranges)...);
  auto state  = step(std::forward<StateT>(initial),
                     std::forward<InputTs>(*std::get<Indices>(firsts))...);

  meta::noop(++std::get<Indices>(firsts)...);
  while (!state_is_reduced(state) && detail::tuple_all_neq(firsts, lasts)) {
    auto new_state = step(std::move(state),
                          std::forward<InputTs>(*std::get<Indices>(firsts))...);
    state = std::move(new_state);
    meta::noop(++std::get<Indices>(firsts)...);
  }

  return state;
}

template <typename T>
struct prop_const_on_range_value_impl
{
  using type = estd::remove_reference_t<decltype(*std::begin(std::declval<T>()))>;
};

template <typename T>
using prop_const_on_range_value_t = typename prop_const_on_range_value_impl<T>::type;

template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce_nested_non_empty_variadic(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_variadic_impl(
      estd::make_index_sequence<sizeof...(InputRangeTs)>{},
      meta::pack<meta::copy_decay_t<
        InputRangeTs,
        prop_const_on_range_value_t<InputRangeTs&&> >...>{},
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeTs>(ranges)...))

} // namespace detail
} // namespace xform
} // namespace atria
