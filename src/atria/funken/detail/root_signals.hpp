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

#include <atria/funken/detail/signals.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace funken {

namespace detail {

/*!
 * Add signal that will always send the current value returned by a
 * given function.
 */
template <typename SensorFnT>
class sensor_down_signal
  : public down_signal<estd::decay_t<estd::result_of_t<SensorFnT()> > >
{
  using base_t = down_signal<estd::decay_t<estd::result_of_t<SensorFnT()> > >;

public:
  sensor_down_signal(SensorFnT sensor)
    : base_t(sensor())
    , sensor_(std::move(sensor))
  {}

  void recompute() final
  {
    this->push_down(sensor_());
  }

private:
  SensorFnT sensor_;
};

/*!
 * Make a StateUpDownSignal with deduced types.
 */
template <typename SensorFnT>
auto make_sensor_signal(SensorFnT&& fn)
  -> std::shared_ptr<sensor_down_signal<estd::decay_t<SensorFnT> > >
{
  return std::make_shared<sensor_down_signal<estd::decay_t<SensorFnT>>>(
    std::forward<SensorFnT>(fn));
}

/*!
 * Root signal that serves as state.
 */
template <typename T>
class state_up_down_signal : public up_down_signal<T>
{
public:
  using value_type = T;

  using up_down_signal<T>::up_down_signal;

  void send_up(const value_type& value) final
  {
    this->push_down(value);
  }

  void send_up(value_type&& value) final
  {
    this->push_down(std::move(value));
  }
};

/*!
 * Make a StateUpDownSignal with deduced types.
 */
template <typename T>
auto make_state_signal(T&& value)
  -> std::shared_ptr<state_up_down_signal<estd::decay_t<T> > >
{
  return std::make_shared<state_up_down_signal<estd::decay_t<T>>>(
    std::forward<T>(value));
}

} // namespace detail

} // namespace funken
} // namespace atria
