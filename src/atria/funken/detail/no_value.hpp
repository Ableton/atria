// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <exception>
#include <atria/meta/utils.hpp>

namespace atria {
namespace funken {

/*!
 * Raised by the view when it produces no value yet. This can happen
 * when the reducing function that it uses is filtering some values.
 */
struct no_value_error : std::exception
{
  const char* what() const noexcept override;
};

namespace detail {

struct no_value : meta::bottom
{
  template <typename T>
  operator T()
  {
    throw no_value_error{};
  }
};

} // namespace detail

} // namespace funken
} // namespace atria
