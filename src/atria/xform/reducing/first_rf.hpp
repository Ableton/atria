// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {

/*!
 * Reducing function that always returns the initial state.
 */
constexpr struct first_rf_t
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&& s, InputTs&& ...) const
    -> StateT&&
  {
    return std::forward<StateT>(s);
  }
} first_rf {};

} // namespace xform
} // namespace atria
