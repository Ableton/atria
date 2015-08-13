// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/impure/transduce.hpp>
#include <atria/xform/reducing/output_rf.hpp>

namespace atria {
namespace xform {
namespace impure {

template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> CollectionT&&
{
  impure::transduce(
    std::forward<XformT>(xform),
    output_rf,
    std::back_inserter(col),
    std::forward<InputRangeTs>(ranges)...);
  return std::forward<CollectionT>(col);
}

} // namesapce impure
} // namespace xform
} // namespace atria
