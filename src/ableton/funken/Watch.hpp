// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/detail/Access.hpp>
#include <ableton/base/meta/Utils.hpp>

namespace ableton {
namespace funken {

template <typename InputValueT, typename CallbackT>
auto watch(InputValueT&& value, CallbackT&& callback)
  -> decltype(
    detail::Access::watchers(value).connect(callback))
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
} // namespace ableton
