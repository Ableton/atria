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

#include <atria/funken/detail/root_signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>

namespace atria {
namespace funken {

template <typename T>
class state : private detail::watchable<T>
{
  using signal_ptr_t = decltype(
    detail::make_state_signal(std::declval<T>()));
public:
  using value_type = T;

  state()
    : signal_(detail::make_state_signal(T())) {}
  state(T value)
    : signal_(detail::make_state_signal(std::move(value))) {}

  state(const state&) = delete;
  state(state&&) = default;
  state& operator=(const state&) = delete;
  state& operator=(state&&) = default;

  template <typename T2>
  void set(T2&& value)
  {
    signal_->push_down(std::forward<T2>(value));
  }

  const T& get() const
  {
    return signal_->last();
  }

private:
  const signal_ptr_t& signal() { return signal_; }
  const signal_ptr_t& roots() { return signal_; }

  friend class detail::access;
  signal_ptr_t signal_;
};

template <typename T>
state<T> make_state(T value)
{
  return value;
}

} // namespace funken
} // namespace atria
