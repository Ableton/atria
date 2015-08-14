// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/meta/utils.hpp>
#include <utility>

namespace atria {
namespace prelude {

/*!
 * @see constantly
 */
template <typename T>
struct constantly_t
{
  T value;

  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) & -> T& { return value; }
  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) const& -> const T& { return value; }
  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) && -> T&& { return std::move(value); }
};

/*!
 * Similar to clojure.core/constantly
 */
template <typename T>
auto constantly(T&& value)
  -> constantly_t<estd::decay_t<T> >
{
  return constantly_t<estd::decay_t<T> >{ std::forward<T>(value) };
}

} // namespace prelude

using prelude::constantly_t;
using prelude::constantly;

} // namespace atria
