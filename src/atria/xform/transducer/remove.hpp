// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/complement.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/remove$1
 */
template <typename PredicateT>
auto remove(PredicateT&& pred)
  -> ABL_DECLTYPE_RETURN(
    filter(complement(std::forward<PredicateT>(pred))))

} // namespace xform
} // namespace atria
