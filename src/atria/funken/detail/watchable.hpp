//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

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
