// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/access.hpp>

namespace atria {
namespace funken {

template <typename InputValueT, typename CallbackT>
auto watch(InputValueT&& value, CallbackT&& callback)
  -> decltype(
    detail::access::watchers(std::forward<InputValueT>(value))
    .connect(std::forward<CallbackT>(callback)))
{
  auto& watchers = detail::access::watchers(
    std::forward<InputValueT>(value));
  if (watchers.empty())
  {
    auto& observers = detail::access::signal(
      std::forward<InputValueT>(value))->observers();
    observers.connect(watchers);
  }
  return watchers.connect(std::forward<CallbackT>(callback));
}

} // namespace funken
} // namespace atria
