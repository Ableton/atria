// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/root_signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>

namespace atria {
namespace funken {

template <typename T>
class State : private detail::watchable<T>
{
  using SignalPtrT = decltype(
    detail::make_state_signal(std::declval<T>()));
public:
  using value_type = T;

  State()
    : mpSignal(detail::make_state_signal(T())) {}
  State(T value)
    : mpSignal(detail::make_state_signal(std::move(value))) {}

  State(const State&) = delete;
  State(State&&) = default;
  State& operator=(const State&) = delete;
  State& operator=(State&&) = default;

  template <typename T2>
  void set(T2&& value)
  {
    mpSignal->push_down(std::forward<T2>(value));
  }

  const T& get() const
  {
    return mpSignal->last();
  }

private:
  const SignalPtrT& signal() { return mpSignal; }
  const SignalPtrT& roots() { return mpSignal; }

  friend class detail::access;
  SignalPtrT mpSignal;
};

template <typename T>
State<T> state(T value)
{
  return value;
}

} // namespace funken
} // namespace atria
