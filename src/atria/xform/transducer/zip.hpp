// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/xform/transducer/map.hpp>

namespace atria {
namespace xform {

/*!
 * Transducer that, if more than one argument is passed, forwards all
 * of them as a single tuple.
 *
 * @todo This should a `constexpr` in C++14
 */
extern const map_t<tuplify_t> zip;

} // namespace xform
} // namespace atria
