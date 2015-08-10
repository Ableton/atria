// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/variant/visitor.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <eggs/variant.hpp>
ABL_RESTORE_WARNINGS
#include <utility>

namespace atria {
namespace variant {

/*!
 * Implementation of @see match for `eggs::visitor`.
 *
 * @todo This function uses `eggs::variants::detail::is_variant`. In
 *       the future we would like to get rid of this.  It is not
 *       extrictly needed, but it makes easier to debug when we try to
 *       use variant-like types that are not detected by the library.
 *
 * @see xform::skip_state for details on `eggs::visitor` limitations.
 */
template <typename VariantT, typename ...Fns>
auto match(VariantT&& variant, Fns&& ...fns)
  -> estd::enable_if_t<
  eggs::variants::detail::is_variant<estd::decay_t<VariantT> >{},
    typename decltype(visitor(std::declval<Fns>()...))::result_type>
{
  using result_t = typename
      decltype(visitor(std::declval<Fns>()...))
    ::result_type;

  return eggs::variants::apply<result_t>(
    visitor(std::forward<Fns>(fns)...),
    std::forward<VariantT>(variant));
}

} // namespace variant
} // namespace atria
