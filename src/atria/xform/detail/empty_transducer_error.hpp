// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <stdexcept>

namespace atria {
namespace xform {
namespace detail {

/*!
 * Error thrown by transducers when they are empty.  The problem is
 * that making an empty transducer requires skipping on the first
 * iteration.  Skipping comes with a cost.  So for performance
 * reasons, a transducer might choose to just rise an error if
 * produces a completely empty sequence.
 *
 * @note This is kept in `detail` because we want to explore
 *       alternative designs that do not require skipping.
 *
 * @see  skip
 *
 * @todo Explore alternative design.
 */
struct empty_transducer_error : std::runtime_error
{
  using base_t = std::runtime_error;
  using base_t::base_t;
  empty_transducer_error() : base_t("empty transducer") {}
};

} // namespace detail
} // namespace xform
} // namespace atria
