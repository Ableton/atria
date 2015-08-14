// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/funken/detail/access.hpp>
#include <atria/meta/utils.hpp>
#include <utility>

namespace atria {
namespace funken {

template <typename ...RootValueTs>
void commit(RootValueTs&& ...roots)
{
  meta::noop(
    (detail::access::roots(std::forward<RootValueTs>(roots))->send_down(),
     meta::can_be_void)...);
  meta::noop(
    (detail::access::roots(std::forward<RootValueTs>(roots))->notify(),
     meta::can_be_void)...);
}

} // namespace funken
} // namespace atria
