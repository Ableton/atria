// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
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
