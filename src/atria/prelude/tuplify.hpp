// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/meta/utils.hpp>
#include <tuple>

namespace atria {
namespace prelude {

/*!
 * Function that forwards its argument if only one element passed,
 * otherwise it makes a tuple.
 */
constexpr struct tuplify_t
{
  constexpr auto operator() () const
    -> ABL_DECLTYPE_RETURN(
      std::tuple<>{})

  template <typename InputT>
  constexpr auto operator() (InputT&& in) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<InputT>(in))

  template <typename InputT, typename ...InputTs>
  constexpr auto operator() (InputT&& in, InputTs&& ...ins) const
    -> ABL_DECLTYPE_RETURN(
      std::make_tuple(std::forward<InputT>(in),
                      std::forward<InputTs>(ins)...))
} tuplify {};

} // namespace prelude

using prelude::tuplify_t;
using prelude::tuplify;

} // namespace atria
