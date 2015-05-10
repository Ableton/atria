// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/reduce.hpp>
#include <atria/xform/reducers.hpp>

namespace atria {
namespace xform {

//!
// Similar to clojure.core/transduce
//
template <typename XformT,
          typename ReducerT,
          typename StateT,
          typename ...InputRangeTs>
auto transduce(XformT&& xform, ReducerT&& reducer,
               StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  auto xformed = xform(std::forward<ReducerT>(reducer));
  return reduce(
    xformed,
    state,
    std::forward<InputRangeTs>(ranges)...);
}

#define ABL_STATEFUL_INTO 1

//!
// Similar to clojure.core/into$4
//
#if ABL_STATEFUL_INTO
template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> CollectionT&&
{
  transduce(
    std::forward<XformT>(xform),
    output_r,
    std::back_inserter(col),
    std::forward<InputRangeTs>(ranges)...);
  return std::forward<CollectionT>(col);
}
#endif

#if !ABL_STATEFUL_INTO
template <typename CollectionT,
          typename XformT,
          typename ...InputRangeTs>
auto into(CollectionT&& col, XformT&& xform, InputRangeTs&& ...ranges)
  -> estd::decay_t<CollectionT>
{
  return transduce(
    std::forward<XformT>(xform),
    emplace_back_r,
    std::forward<CollectionT>(col),
    std::forward<InputRangeTs>(ranges)...);
}
#endif

} // namespace xform
} // namespace atria
