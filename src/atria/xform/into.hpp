// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/config.hpp>
#include <atria/xform/transduce.hpp>
#if ABL_STATEFUL_INTO
#include <atria/xform/reducing/output_rf.hpp>
#else
#include <atria/xform/reducing/emplace_back_rf.hpp>
#endif

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/into$4
 */
#if ABL_STATEFUL_INTO

template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> CollectionT&&
{
  transduce(
    std::forward<XformT>(xform),
    output_rf,
    std::back_inserter(col),
    std::forward<InputRangeTs>(ranges)...);
  return std::forward<CollectionT>(col);
}

#else

template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> estd::decay_t<CollectionT>
{
  return transduce(
    std::forward<XformT>(xform),
    emplace_back_rf,
    std::forward<CollectionT>(col),
    std::forward<InputRangeTs>(ranges)...);
}

#endif

} // namespace xform
} // namespace atria
