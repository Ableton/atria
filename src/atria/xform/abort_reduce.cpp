// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/abort_reduce.hpp>

namespace atria {
namespace xform {
namespace impure {

const char* reduce_aborted_error_base::what() const noexcept
{
  return "Reduction aborted";
}

} // namespace impure
} // namespace xform
} // namespace atria
