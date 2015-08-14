// Copyright: 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/variant/variant_types.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <eggs/variant/variant.hpp>
ABL_RESTORE_WARNINGS

namespace atria {
namespace variant {

template <typename... Ts>
struct variant_types_impl<eggs::variants::variant<Ts...> >
{
  using type = meta::pack<Ts...>;
};

} // namespace variant
} // namespace atria
