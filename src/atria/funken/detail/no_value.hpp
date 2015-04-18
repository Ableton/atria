// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <exception>

namespace atria {
namespace funken {

//!
// Raised by the view when it produces no value yet. This can happen
// when the reducer that it uses is filtering some values.
//
struct no_value_error : std::exception
{
  const char* what() const noexcept override
  { return "No value in funken object"; }
};

namespace detail {

struct no_value
{
  template <typename T> operator T&() { throw no_value_error{}; }
  template <typename T> operator const T&() { throw no_value_error{}; }
};

} // namespace detail

} // namespace funken
} // namespace atria
