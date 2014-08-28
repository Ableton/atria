// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/detail/Access.hpp>
#include <ableton/base/meta/Utils.hpp>

namespace ableton {
namespace funken {

template <typename ...RootValueTs>
void commit(RootValueTs&& ...roots)
{
  base::meta::noop(
    (detail::Access::roots(std::forward<RootValueTs>(roots))->sendDown(),
     42)...);
  base::meta::noop(
    (detail::Access::roots(std::forward<RootValueTs>(roots))->notify(),
     42)...);
}

} // namespace funken
} // namespace ableton
