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

// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/funken/detail/signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>
#include <atria/funken/concepts.hpp>

namespace atria {
namespace funken {

namespace detail {

template <typename SignalT>
class output_impl
{
  template <typename T> friend class output_impl;
  friend class detail::access;

  using signal_ptr_t = std::shared_ptr<SignalT>;
  signal_ptr_t signal_;
  const signal_ptr_t& signal() const { return signal_; }

public:
  using value_type = meta::value_t<SignalT>;

  output_impl() = default;
  output_impl(output_impl&&) = default;
  output_impl& operator=(output_impl&&) = default;
  output_impl(const output_impl&) = delete;
  output_impl& operator=(const output_impl&) = delete;

  template <typename T>
  output_impl& operator=(output_impl<T>&& x)
  {
    signal_ = std::move(x.signal_);
    return *this;
  }

  template <typename T>
  output_impl(output_impl<T>&& x)
    : signal_(std::move(x.signal_))
  {}

  output_impl(signal_ptr_t sig)
    : signal_(std::move(sig)) {}

  template <typename T>
  void set(T&& value)
  {
    return signal_->send_up(std::forward<T>(value));
  }
};

} // namespace detail

/*!
 * Provides access to writing values of type `T`.
 * Model of `Output_value`.
 * @see `Output_value`
 */
template <typename T>
class output : public detail::output_impl<detail::up_down_signal<T> >
{
  using base_t = detail::output_impl<detail::up_down_signal<T> >;
public:
  using base_t::base_t;
  using base_t::operator=;
};

/*!
 * Creates an out from another out value.
 * @see `output<T>`
 */
template <typename OutT>
auto out(OutT&& object)
  -> estd::enable_if_t<
    (Out_value<OutT>()),
    detail::output_impl<detail::signal_type_t<OutT> > >
{
  return detail::access::signal(std::forward<OutT>(object));
}

} // namespace funken
} // namespace atria
