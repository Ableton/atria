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

//!
// Similar to clojure.core/transduce$4
//
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

} // namespace xform
} // namespace atria
