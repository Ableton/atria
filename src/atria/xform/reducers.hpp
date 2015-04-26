// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {

//!
// Reducer that returns the last input of the sequence.
//
constexpr struct last_r_t
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&&, InputTs&& ...ins) const
    -> estd::decay_t<decltype(tuplify(std::forward<InputTs>(ins)...))>
  {
    return tuplify(std::forward<InputTs>(ins)...);
  }

  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&& s) const -> StateT&&
  {
    return std::forward<StateT>(s);
  }
} last_r {};

//!
// Reducer that outputs to the iterator that is passed as state.
//
constexpr struct output_r_t
{
  template <typename OutputItT, typename ...InputTs>
  auto operator() (OutputItT it, InputTs&& ...ins) const
    -> OutputItT
  {
    *it = tuplify(std::forward<InputTs>(ins)...);
    return ++it;
  }
} output_r {};

} // namespace xform
} // namespace atria
