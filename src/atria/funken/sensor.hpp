// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/root_signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>

namespace atria {
namespace funken {

template <typename SensorFnT>
class sensor : private detail::watchable<
  estd::decay_t<estd::result_of_t<SensorFnT()> > >
{
  using signal_ptr_t = decltype(
    detail::make_sensor_signal(std::declval<SensorFnT>()));
public:
  using value_type = estd::decay_t<estd::result_of_t<SensorFnT()> >;

  sensor()
    : signal_(detail::make_sensor_signal(SensorFnT())) {}
  sensor(SensorFnT fn)
    : signal_(detail::make_sensor_signal(std::move(fn))) {}

  sensor(const sensor&) = delete;
  sensor(sensor&&) = default;
  sensor& operator=(const sensor&) = delete;
  sensor& operator=(sensor&&) = default;

  const value_type& get() const
  {
    return signal_->last();
  }

private:
  const signal_ptr_t& signal() { return signal_; }
  const signal_ptr_t& roots() { return signal_; }

  friend class detail::access;
  signal_ptr_t signal_;
};

template <typename SensorFnT>
sensor<SensorFnT> make_sensor(SensorFnT fn)
{
  return fn;
}

} // namespace funken
} // namespace atria
