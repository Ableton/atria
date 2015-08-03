// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/trace.hpp>

namespace atria {
namespace xform {

/*!
 * Transducer that traces the values values that pass through it and
 * forwards them forward in the chain.
 *
 * @see trace
 * @see tracer
 */
inline auto traced(std::string message)
  -> ABL_DECLTYPE_RETURN(
    map(tracer{std::move(message)}));

} // namespace xform
} // namespace atria
