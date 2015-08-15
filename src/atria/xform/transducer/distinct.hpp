// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/skip.hpp>
#include <atria/estd/tuple_hash.hpp>
#include <atria/prelude/tuplify.hpp>
#include <atria/estd/functional.hpp>
#include <unordered_set>

namespace atria {
namespace xform {

namespace detail {

struct distinct_rf_gen
{
  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    template <typename ...InputTs>
    using cache_t = std::unordered_set<
        estd::decay_t<
          decltype(tuplify(std::declval<InputTs>()...))> >;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state(
          call(step,
               state_unwrap(std::forward<StateT>(s)),
               std::forward<InputTs>(is)...),
          cache_t<InputTs...>{}))
    {
      auto cache = state_data(std::forward<StateT>(s), []{
          return cache_t<InputTs...>{};
        });

      auto unique = cache.insert(tuplify(is...)).second;
      return wrap_state(
          unique
            ? call(step,
                   state_unwrap(std::forward<StateT>(s)),
                   std::forward<InputTs>(is)...)
            : skip(step,
                   state_unwrap(std::forward<StateT>(s)),
                   std::forward<InputTs>(is)...),
          std::move(cache));
    }
  };
};

} // namespace detail

using distinct_t = transducer_impl<detail::distinct_rf_gen>;

/*!
 * Equivalent to clojure/distinct$0
 */
constexpr distinct_t distinct {};

} // namespace xform
} // namespace atria
