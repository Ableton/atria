// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/detail/RootSignals.hpp>
#include <ableton/funken/detail/Access.hpp>
#include <ableton/funken/detail/Watchable.hpp>

namespace ableton {
namespace funken {

template <typename T>
class State : private detail::Watchable<T>
{
  using SignalPtrT = decltype(
    detail::makeStateSignal(std::declval<T>()));
public:
  using value_type = T;

  State()
    : mpSignal(detail::makeStateSignal(T())) {}
  State(const T& value)
    : mpSignal(detail::makeStateSignal(value)) {}
  State(T&& value)
    : mpSignal(detail::makeStateSignal(std::move(value))) {}

  State(const State&) = delete;
  State(State&&) = default;
  State& operator=(const State&) = delete;
  State& operator=(State&&) = default;

  template <typename T2>
  void set(T2&& value)
  {
    mpSignal->pushDown(std::forward<T2>(value));
  }

  const T& get() const
  {
    return mpSignal->last();
  }

private:
  const SignalPtrT& signal() { return mpSignal; }
  const SignalPtrT& roots() { return mpSignal; }

  friend class detail::Access;
  SignalPtrT mpSignal;
};

template <typename T>
State<T> state(T value)
{
  return value;
}

} // namespace funken
} // namespace ableton
