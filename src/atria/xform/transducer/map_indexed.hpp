// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/count.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/map-indexed$1
 */
template <typename MappingT>
constexpr auto map_indexed(MappingT&& mapping)
  -> ABL_DECLTYPE_RETURN(
    comp(
      count(),
      map(std::forward<MappingT>(mapping))))

} // namespace xform
} // namespace atria
