// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/xform/transducer/cat.hpp>
#include <atria/xform/transducer/map.hpp>

namespace atria {
namespace xform {

//!
// Similar to clojure.core/mapcat$1
//
template <typename MappingT>
auto mapcat(MappingT&& mapping)
  -> ABL_AUTO_RETURN(
    comp(
      cat,
      map(std::forward<MappingT>(mapping))))

} // namespace xform
} // namespace atria
