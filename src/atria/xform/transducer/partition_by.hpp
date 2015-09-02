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

#include <atria/xform/reduce.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/skip.hpp>
#include <atria/estd/functional.hpp>
#include <vector>

namespace atria {
namespace xform {

namespace detail {

struct partition_by_rf_gen
{
  struct tag {};

  template <typename ReducingFnT,
            typename MappingT>
  struct apply
  {
    ReducingFnT step;
    MappingT mapping;

    template <typename ...InputTs>
    using container_t = std::vector<
      estd::decay_t<
        decltype(tuplify(std::declval<InputTs>()...))> >;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state<tag>(
          skip(step, state_unwrap(s), container_t<InputTs...>{}),
          make_tuple(mapping(is...), container_t<InputTs...>{}, step)))
    {
      auto mapped = estd::invoke(mapping, std::forward<InputTs>(is)...);

      auto data = state_data(std::forward<StateT>(s), [&] {
          auto v = container_t<InputTs...>{};
          return make_tuple(mapped, std::move(v), step);
        });

      auto& last_mapped = std::get<0>(data);
      auto& next_vector = std::get<1>(data);
      auto& next_step   = std::get<2>(data);

      const auto complete_group = mapped != last_mapped;

      auto next_state = complete_group
        ? call(step, state_unwrap(std::forward<StateT>(s)), next_vector)
        : skip(step, state_unwrap(std::forward<StateT>(s)), next_vector);

      if (complete_group)
        next_vector.clear();

      next_vector.push_back(tuplify(std::forward<InputTs>(is)...));

      return wrap_state<tag> (
        std::move(next_state),
        make_tuple(std::move(mapped),
                   std::move(next_vector),
                   std::move(next_step)));
    }
  };

  template <typename T>
  friend auto state_wrapper_complete(tag, T&& wrapper)
    -> decltype(state_complete(state_unwrap(std::forward<T>(wrapper))))
  {
    auto next = std::get<1>(state_wrapper_data(std::forward<T>(wrapper)));
    auto step = std::get<2>(state_wrapper_data(std::forward<T>(wrapper)));
    return state_complete(
      next.empty()
      ? state_unwrap(std::forward<T>(wrapper))
      : step(state_unwrap(std::forward<T>(wrapper)), std::move(next)));
  }
};

} // namespace detail

template <typename T>
using partition_by_t = transducer_impl<detail::partition_by_rf_gen, T>;

/*!
 * Similar to clojure.core/partition-by$1
 */
template <typename MappingT>
auto partition_by(MappingT&& mapping)
  -> partition_by_t<estd::decay_t<MappingT> >
{
  return partition_by_t<estd::decay_t<MappingT> > { mapping };
}

} // namespace xform
} // namespace atria
