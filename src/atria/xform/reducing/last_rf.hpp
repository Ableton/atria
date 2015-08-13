// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/utility.hpp>
#include <atria/estd/type_traits.hpp>
#include <atria/prelude/tuplify.hpp>

namespace atria {
namespace xform {

/*!
 * Reducing function that emplaces back at the collection that is
 * uses as state.
 */
constexpr struct last_rf_t
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&&, InputTs&& ...ins) const
    -> estd::decay_t<decltype(tuplify(std::forward<InputTs>(ins)...))>
  {
    return tuplify(std::forward<InputTs>(ins)...);
  }

  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&& s) const
    -> StateT&&
  {
    return std::forward<StateT>(s);
  }
} last_rf {};

} // namespace xform
} // namespace atria
