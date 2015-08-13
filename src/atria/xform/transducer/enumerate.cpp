// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/transducer/enumerate.hpp>

namespace atria {
namespace xform {

#if !ABL_CXX14
const enumerate_t<std::size_t> enumerate = enumerate_from(std::size_t{});
#endif

} // namespace xform
} // namespace atria
