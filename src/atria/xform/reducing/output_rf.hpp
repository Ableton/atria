
// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {

/*!
 * Reducing function that outputs through the iterator that is carried
 * as state.
 */
constexpr struct output_rf_t
{
  template <typename OutputItT, typename ...InputTs>
  auto operator() (OutputItT it, InputTs&& ...ins) const
    -> OutputItT
  {
    *it = tuplify(std::forward<InputTs>(ins)...);
    return ++it;
  }
} output_rf {};

} // namespace xform
} // namespace atria
