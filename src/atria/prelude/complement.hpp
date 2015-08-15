// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <utility>
#include <atria/meta/utils.hpp>
#include <atria/estd/type_traits.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace prelude {

template <typename FnT>
struct complement_t
{
  FnT fn;

  template <typename... ArgTs>
  auto operator() (ArgTs&& ...args)
    -> ABL_DECLTYPE_RETURN(
      !estd::invoke(fn, std::forward<ArgTs>(args)...))
};

/*!
 * Similar to clojure.core/complement$1
 *
 * `fn` is invoked via standard *INVOKE*, allowing to negate function
 * pointers, member functions, etc.
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
