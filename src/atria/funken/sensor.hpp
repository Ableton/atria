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
