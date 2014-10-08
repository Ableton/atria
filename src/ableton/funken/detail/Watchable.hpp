// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/signals2/signal.hpp>
ABL_RESTORE_WARNINGS

namespace ableton {
namespace funken {

namespace detail {

template <typename ValueT>
class Watchable
{
  using WatchersT = boost::signals2::signal<
    void (const ValueT&, const ValueT&)>;
  WatchersT mWatchers;

public:
  Watchable() = default;
  Watchable(Watchable&& other) noexcept
  {
    mWatchers.swap(other.mWatchers);
  }
  Watchable& operator=(Watchable&& other) noexcept
  {
    mWatchers.swap(other.mWatchers);
    return *this;
  }

  WatchersT& watchers() { return mWatchers; }
};

} // namespace detail

} // namespace funken
} // namespace ableton
