// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/utils.hpp>
#include <iostream>

namespace atria {
namespace xform {

/*!
 * Prints "<message> <x>" to `std::cerr` and returns the value,
 * forwarded.  Useful for looking at the value that is returned in the
 * middle of an expression.
 *
 * @see tracer
 * @see traced
 */
template <typename T>
auto trace(T&& x, const std::string& message)
  -> ABL_DECLTYPE_RETURN(
    (std::cerr << message << " " << x << std::endl,
     std::forward<T>(x)))

/*!
 * Function object for calling @a trace
 *
 * @see trace
 * @see traced
 */
struct tracer
{
  std::string message;

  template <typename T>
  auto operator() (T&& x)
    -> ABL_DECLTYPE_RETURN(
    trace(std::forward<T>(x), message))
};

} // namespace xform
} // namespace atria
