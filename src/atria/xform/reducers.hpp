// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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
// Reducer that returns the initial state
//
constexpr struct first_r_t
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT&& s, InputTs&& ...) const
    -> StateT&&
  {
    return std::forward<StateT>(s);
  }
} first_r {};

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

//!
// Reducer that emplaces back at the collection that it is passed.
//
constexpr struct emplace_back_r_t
{
  template <typename CollectionT, typename ...InputTs>
  auto operator() (CollectionT c, InputTs&& ...ins) const
    -> CollectionT
  {
    c.emplace_back(std::forward<InputTs>(ins)...);
    return c;
  }
} emplace_back_r {};

} // namespace xform
} // namespace atria
