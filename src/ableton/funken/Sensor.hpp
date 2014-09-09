// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/detail/RootSignals.hpp>
#include <ableton/funken/detail/Access.hpp>
#include <ableton/funken/detail/Watchable.hpp>

namespace ableton {
namespace funken {

template <typename SensorFnT>
class Sensor : private detail::Watchable<
  estd::decay_t<estd::result_of_t<SensorFnT()> > >
{
  using SignalPtrT = decltype(
    detail::makeSensorSignal(std::declval<SensorFnT>()));
public:
  using value_type = estd::decay_t<estd::result_of_t<SensorFnT()> >;

  Sensor()
    : mpSignal(detail::makeSensorSignal(SensorFnT())) {}
  Sensor(const SensorFnT& fn)
    : mpSignal(detail::makeSensorSignal(fn)) {}
  Sensor(SensorFnT&& fn)
    : mpSignal(detail::makeSensorSignal(std::move(fn))) {}

  Sensor(const Sensor&) = delete;
  Sensor(Sensor&&) = default;
  Sensor& operator=(const Sensor&) = delete;
  Sensor& operator=(Sensor&&) = default;

  const value_type& get() const
  {
    return mpSignal->last();
  }

private:
  const SignalPtrT& signal() { return mpSignal; }
  const SignalPtrT& roots() { return mpSignal; }

  friend class detail::Access;
  SignalPtrT mpSignal;
};

template <typename SensorFnT>
Sensor<SensorFnT> sensor(SensorFnT fn)
{
  return fn;
}

} // namespace funken
} // namespace ableton
