// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/Signals.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace funken {

namespace detail {

//!
// Add signal that will always send the current value returned by a
// given function.
//
template <typename SensorFnT>
class SensorDownSignal
  : public DownSignal<estd::decay_t<estd::result_of_t<SensorFnT()> > >
{
  using BaseT = DownSignal<estd::decay_t<estd::result_of_t<SensorFnT()> > >;

public:
  SensorDownSignal(SensorFnT sensor)
    : BaseT(sensor())
    , mSensor(std::move(sensor))
  {}

  void recompute() final
  {
    this->pushDown(mSensor());
  }

private:
  SensorFnT mSensor;
};

//!
// Make a StateUpDownSignal with deduced types.
//
template <typename SensorFnT>
auto makeSensorSignal(SensorFnT&& fn)
  -> std::shared_ptr<SensorDownSignal<estd::decay_t<SensorFnT> > >
{
  return std::make_shared<SensorDownSignal<estd::decay_t<SensorFnT>>>(
    std::forward<SensorFnT>(fn));
}

//!
// Root signal that serves as state.
//
template <typename T>
class StateUpDownSignal : public UpDownSignal<T>
{
public:
  using value_type = T;

  using UpDownSignal<T>::UpDownSignal;

  void sendUp(const value_type& value) final
  {
    this->pushDown(value);
  }

  void sendUp(value_type&& value) final
  {
    this->pushDown(std::move(value));
  }
};

//!
// Make a StateUpDownSignal with deduced types.
//
template <typename T>
auto makeStateSignal(T&& value)
  -> std::shared_ptr<StateUpDownSignal<estd::decay_t<T> > >
{
  return std::make_shared<StateUpDownSignal<estd::decay_t<T>>>(
    std::forward<T>(value));
}

} // namespace detail

} // namespace funken
} // namespace atria
