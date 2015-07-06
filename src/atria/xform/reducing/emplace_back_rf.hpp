// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {

/*!
 * Reducing function that emplaces back at the collection that is
 * uses as state.
 */
constexpr struct emplace_back_rf_t
{
  template <typename CollectionT, typename ...InputTs>
  auto operator() (CollectionT c, InputTs&& ...ins) const
    -> CollectionT
  {
    c.emplace_back(std::forward<InputTs>(ins)...);
    return c;
  }
} emplace_back_rf {};

} // namespace xform
} // namespace atria
