// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/root_signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>

namespace atria {
namespace funken {

template <typename SensorFnT>
class Sensor : private detail::watchable<
  estd::decay_t<estd::result_of_t<SensorFnT()> > >
{
  using SignalPtrT = decltype(
    detail::make_sensor_signal(std::declval<SensorFnT>()));
public:
  using value_type = estd::decay_t<estd::result_of_t<SensorFnT()> >;

  Sensor()
    : mpSignal(detail::make_sensor_signal(SensorFnT())) {}
  Sensor(SensorFnT fn)
    : mpSignal(detail::make_sensor_signal(std::move(fn))) {}

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

  friend class detail::access;
  SignalPtrT mpSignal;
};

template <typename SensorFnT>
Sensor<SensorFnT> sensor(SensorFnT fn)
{
  return fn;
}

} // namespace funken
} // namespace atria
