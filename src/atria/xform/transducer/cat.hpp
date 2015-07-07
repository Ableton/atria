// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/reduce.hpp>

namespace atria {
namespace xform {

namespace detail {

struct cat_rf_gen
{
  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        reduce_nested(step,
                      std::forward<State>(s),
                      std::forward<Inputs>(is)...))
  };
};

} // namespace detail

/*!
 * Similar to clojure.core/cat$1
 */
constexpr auto cat = transducer_impl<detail::cat_rf_gen> {};

} // namespace xform
} // namespace atria
