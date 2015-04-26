// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/signals2/signal.hpp>
ABL_RESTORE_WARNINGS

namespace atria {
namespace funken {

namespace detail {

template <typename ValueT>
class watchable
{
  using WatchersT = boost::signals2::signal<
    void (const ValueT&, const ValueT&)>;
  WatchersT watchers_;

public:
  watchable() = default;
  watchable(watchable&& other) noexcept
  {
    watchers_.swap(other.watchers_);
  }
  watchable& operator=(watchable&& other) noexcept
  {
    watchers_.swap(other.watchers_);
    return *this;
  }

  WatchersT& watchers() { return watchers_; }
};

} // namespace detail

} // namespace funken
} // namespace atria
