// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/into.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <vector>

namespace atria {
namespace xform {

namespace detail {

template <typename XformT, typename... InputRangeTs>
struct into_vector_result
{
  using xformed_t = decltype(
    state_complete(
      std::declval<XformT>()(last_rf)(
        std::declval<meta::bottom>(),
        std::declval<estd::Value_type<InputRangeTs> >()...)));

  using type = std::vector<estd::decay_t<xformed_t> >;
};

template <typename XformT, typename... InputRangeTs>
using into_vector_result_t = typename
  into_vector_result<XformT, InputRangeTs...>::type;

} // namespace detail

/*!
 * Similar to clojure.core/into-array
 */
template <typename XformT,
          typename ...InputRangeTs>
auto into_vector(XformT&& xform, InputRangeTs&& ...ranges)
  -> detail::into_vector_result_t<XformT, InputRangeTs...>
{
  return into(detail::into_vector_result_t<XformT, InputRangeTs...>{},
              std::forward<XformT>(xform),
              std::forward<InputRangeTs>(ranges)...);
}

} // namespace xform
} // namespace atria
