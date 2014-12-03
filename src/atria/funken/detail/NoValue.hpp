// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <exception>

namespace atria {
namespace funken {

//!
// Raised by the view when it produces no value yet. This can happen
// when the reducer that it uses is filtering some values.
//
struct NoValueError : std::exception
{
  const char* what() const noexcept override
  { return "No value in funken object"; }
};

namespace detail {

struct NoValue
{
  template <typename T> operator T&() { throw NoValueError{}; }
  template <typename T> operator const T&() { throw NoValueError{}; }
};

} // namespace detail

} // namespace funken
} // namespace atria
