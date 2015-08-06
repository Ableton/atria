// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/transducer/enumerate.hpp>

namespace atria {
namespace xform {

const enumerate_t<std::size_t> enumerate = enumerate_from(std::size_t{});

namespace impure {

const enumerate_t<std::size_t> enumerate = enumerate_from(std::size_t{});

} // namspace impure

} // namespace xform
} // namespace atria
