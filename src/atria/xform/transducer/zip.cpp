// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/prelude/tuplify.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/zip.hpp>

namespace atria {
namespace xform {

#if !ABL_CXX14
const map_t<tuplify_t> zip = map(tuplify);
#endif

} // namespace xform
} // namespace atria
