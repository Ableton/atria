// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/base/variant/Visitor.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant/apply_visitor.hpp>
ABL_RESTORE_WARNINGS
#include <utility>

namespace ableton {
namespace base {
namespace variant {

template <typename VariantT, typename ...Fns>
typename decltype(visitor(std::declval<Fns>()...))::result_type
match(VariantT& variant, Fns&& ...fns)
{
  auto visit = visitor(std::forward<Fns>(fns)...);
  return boost::apply_visitor(visit, variant);
}

template <typename VariantT, typename ...Fns>
typename decltype(visitor(std::declval<Fns>()...))::result_type
match(const VariantT& variant, Fns&& ...fns)
{
  auto visit = visitor(std::forward<Fns>(fns)...);
  return variant.apply_visitor(visit);
}

} // namespace variant
} // namespace base
} // namespace ableton
