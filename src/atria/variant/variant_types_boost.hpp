// Copyright: 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/variant/variant_types.hpp>
#include <boost/variant.hpp>

namespace atria {
namespace variant {

template <typename T, typename... Ts>
struct variant_types_impl<boost::variant<T, Ts...> >
{
  using type = meta::pack<T, Ts...>;
};

} // namespace variant
} // namespace atria
