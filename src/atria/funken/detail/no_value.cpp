// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/detail/no_value.hpp>

namespace atria {
namespace funken {

const char* no_value_error::what() const noexcept
{
  return "No value in funken object";
}

} // namespace funken
} // namespace atria
