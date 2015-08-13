// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/prelude/tuplify.hpp>
#include <atria/xform/transducer/map.hpp>

namespace atria {
namespace xform {

/*!
 * Transducer that, if more than one argument is passed, forwards all
 * of them as a single tuple.
 *
 * @todo This should a `constexpr` in C++14
 */
#if ABL_CXX14
auto zip = map(tuplify);
#else
extern const map_t<tuplify_t> zip;
#endif

} // namespace xform
} // namespace atria
