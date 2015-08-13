// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <utility>
#include <atria/meta/utils.hpp>

namespace atria {
namespace prelude {

template <typename FnT>
struct complement_t
{
  FnT fn;

  template <typename... ArgTs>
  auto operator() (ArgTs&& ...args)
    -> ABL_DECLTYPE_RETURN(
      fn(std::forward<ArgTs>(args)...))
};

/*!
 * Similar to clojure.core/complement$1
 */
template <typename FnT>
auto complement(FnT&& fn)
  -> complement_t<estd::decay_t<FnT> >
{
  return { std::forward<FnT>(fn) };
}

} // namespace prelude

using prelude::complement_t;
using prelude::complement;

} // namespace atria
