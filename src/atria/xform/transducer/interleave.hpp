// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/reduce.hpp>

namespace atria {
namespace xform {

namespace detail {

struct interleave_rf_gen
{
  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    template <typename StateT>
    auto impl(StateT&& s) -> StateT&&
    {
      return std::forward<StateT>(s);
    }

    template <typename StateT, typename InputT, typename ...InputTs>
    auto impl(StateT&& s, InputT&& i, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s), std::forward<InputT>(i)))
    {
      return !state_is_reduced(s)
        ? impl(step(std::forward<StateT>(s), std::forward<InputT>(i)),
               std::forward<InputTs>(is)...)
        : std::forward<StateT>(s);
    }


    template <typename StateT, typename InputT, typename ...InputTs>
    auto operator() (StateT&& s, InputT&& i, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s), std::forward<InputT>(i)))
    {
      return impl(step(std::forward<StateT>(s), std::forward<InputT>(i)),
                  std::forward<InputTs>(is)...);
    }
  };
};

} // namespace detail

using interleave_t = transducer_impl<detail::interleave_rf_gen>;

/*!
 * Similar to clojure.core/interleave$1
 */
constexpr auto interleave = interleave_t {};

} // namespace xform
} // namespace atria
