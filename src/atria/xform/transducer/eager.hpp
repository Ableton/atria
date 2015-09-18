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

#include <atria/xform/reduce_nested.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/prelude/tuplify.hpp>
#include <atria/prelude/identity.hpp>
#include <vector>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/iterator_range.hpp>
ABL_RESTORE_WARNINGS
#include <functional>

namespace atria {
namespace xform {

namespace detail {

struct eager_rf_gen
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

    template <typename ...InputTs>
    using data_t = std::tuple<
      container_t<InputTs...>,
      std::reference_wrapper<apply> >;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state<tag>(
          state_unwrap(std::forward<StateT>(s)),
          std::declval<data_t<InputTs...>>()))
    {
      auto data = state_data(std::forward<StateT>(s), [&] {
          return data_t<InputTs...>(container_t<InputTs...>{}, *this);
        });

      std::get<0>(data).push_back(tuplify(std::forward<InputTs>(is)...));

      return wrap_state<tag> (
        state_unwrap(std::forward<StateT>(s)),
        std::move(data));
    }
  };

  template <typename T>
  friend auto state_wrapper_complete(tag, T&& wrapper)
    -> ABL_DECLTYPE_RETURN(
      identity_(
        state_complete(
          reduce_nested(
            std::get<1>(state_wrapper_data(std::forward<T>(wrapper))).get().step,
            state_unwrap(std::forward<T>(wrapper)),
            std::get<1>(state_wrapper_data(std::forward<T>(wrapper))).get().mapping(
              std::get<0>(state_wrapper_data(std::forward<T>(wrapper))))))))
};

} // namespace detail

template <typename T>
using eager_t = transducer_impl<detail::eager_rf_gen, T>;

/*!
 * Similar to clojure.core/eager-all$1
 */
template <typename MappingT>
auto eager(MappingT&& mapping)
  -> eager_t<estd::decay_t<MappingT> >
{
  return eager_t<estd::decay_t<MappingT> > { mapping };
}

namespace detail {

struct sorted_range_t
{
  template <typename RangeT>
  auto operator() (RangeT&& range) -> RangeT&&
  {
    std::sort(range.begin(), range.end());
    return std::forward<RangeT>(range);
  }
};

} // namespace

using sorted_t = eager_t<detail::sorted_range_t>;

/*!
 * Eager transducer that sorts the input sequence.
 * @see eager
 */
constexpr sorted_t sorted {};

namespace detail {

struct reversed_range_t
{
  template <typename RangeT>
  auto operator() (RangeT&& range)
    -> ABL_DECLTYPE_RETURN(
      boost::make_iterator_range(
        range.rbegin(),
        range.rend()))
};

} // namespace

using reversed_t = eager_t<detail::reversed_range_t>;

/*!
 * Eager transducer that reverses the input sequence.
 * @see eager
 */
constexpr reversed_t reversed {};

} // namespace xform
} // namespace atria
