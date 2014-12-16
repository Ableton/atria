// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/Access.hpp>
#include <atria/meta/Utils.hpp>
#include <utility>

namespace atria {
namespace funken {

template <typename ...RootValueTs>
void commit(RootValueTs&& ...roots)
{
  meta::noop(
    (detail::Access::roots(std::forward<RootValueTs>(roots))->sendDown(),
     meta::canBeVoid)...);
  meta::noop(
    (detail::Access::roots(std::forward<RootValueTs>(roots))->notify(),
     meta::canBeVoid)...);
}

} // namespace funken
} // namespace atria
