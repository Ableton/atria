// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/functional.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/zip.hpp>

namespace atria {
namespace xform {

const map_t<tuplify_t> zip = map(tuplify);

} // namespace xform
} // namespace atria
