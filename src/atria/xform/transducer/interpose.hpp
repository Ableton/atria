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

#include <atria/xform/detail/empty_transducer_error.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/with_state.hpp>
#include <atria/meta/copy_traits.hpp>

namespace atria {
namespace xform {

namespace detail {

struct interpose_rf_gen
{
  template <typename ReducingFnT,
            typename IndexSequenceT,
            typename ValueT>
  struct apply
  {
    ReducingFnT step;
    IndexSequenceT indices;
    ValueT value;

    template <std::size_t... Indices, typename StateT>
    auto interp(estd::index_sequence<Indices...>, StateT&& s)
      -> ABL_DECLTYPE_RETURN(
        step(std::forward<StateT>(s), std::get<Indices>(value)...))

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), is...)))
    {
      using std::begin;
      using std::end;

      using result_t   = decltype(wrap_state(step(state_unwrap(s), is...)));
      using complete_t = decltype(state_complete(s));

      using wrapped_t   = meta::copy_decay_t<StateT, estd::decay_t<result_t>>;
      using unwrapped_t = meta::copy_decay_t<StateT, estd::decay_t<complete_t>>;

      return with_state(
        std::forward<StateT>(s),
        [&] (unwrapped_t&& st) {
          return wrap_state(
            step(std::forward<unwrapped_t>(st),
                 std::forward<InputTs>(is)...));
        },
        [&] (wrapped_t&& st) {
          auto next = interp(indices, state_unwrap(std::forward<wrapped_t>(st)));
          return wrap_state(
            !state_is_reduced(next)
              ? step(std::move(next), std::forward<InputTs>(is)...)
              : std::move(next));
        });
    }
  };
};

} // namespace detail

template <typename T1, typename T2>
using interpose_t = transducer_impl<detail::interpose_rf_gen, T1, T2>;

/*!
 * Like clojure.core/interpose$1
 */
template <typename... ValueTs>
constexpr auto interpose(ValueTs&& ...xs)
  -> interpose_t<estd::make_index_sequence<sizeof...(ValueTs)>,
                 std::tuple<estd::decay_t<ValueTs>...> >
{
  using indices_t = estd::make_index_sequence<sizeof...(ValueTs)>;

  return interpose_t<indices_t, std::tuple<estd::decay_t<ValueTs>...> > {
    indices_t{},
    std::make_tuple(std::forward<ValueTs>(xs)...)
  };
}

} // namespace xform
} // namespace atria
