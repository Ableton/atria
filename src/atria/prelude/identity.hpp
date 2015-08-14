// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/meta/utils.hpp>

namespace atria {
namespace prelude {

/*!
 * Similar to clojure.core/identity
 */
constexpr struct identity_t
{
  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<ArgT>(x))
} identity {};

} // namespace prelude

using prelude::identity_t;
using prelude::identity;

} // namespace atria
