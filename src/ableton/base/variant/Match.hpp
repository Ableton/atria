// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/base/variant/Visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
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
