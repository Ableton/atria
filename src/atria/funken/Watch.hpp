// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/Access.hpp>

namespace atria {
namespace funken {

template <typename InputValueT, typename CallbackT>
auto watch(InputValueT&& value, CallbackT&& callback)
  -> decltype(
    detail::Access::watchers(std::forward<InputValueT>(value))
    .connect(std::forward<CallbackT>(callback)))
{
  auto& watchers = detail::Access::watchers(
    std::forward<InputValueT>(value));
  if (watchers.empty())
  {
    auto& observers = detail::Access::signal(
      std::forward<InputValueT>(value))->observers();
    observers.connect(watchers);
  }
  return watchers.connect(std::forward<CallbackT>(callback));
}

} // namespace funken
} // namespace atria
