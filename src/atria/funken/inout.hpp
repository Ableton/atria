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
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>
#include <atria/funken/concepts.hpp>

namespace atria {
namespace funken {

namespace detail {

template <typename SignalT>
class inoutput_impl
  : private watchable<meta::value_t<SignalT> >
{
  template <typename T> friend class inoutput_impl;
  friend class detail::access;

  using base_t = watchable<meta::value_t<SignalT> >;

  using signal_ptr_t = std::shared_ptr<SignalT>;
  signal_ptr_t signal_;
  const signal_ptr_t& signal() const { return signal_; }

public:
  using value_type = meta::value_t<SignalT>;

  inoutput_impl(signal_ptr_t sig)
    : signal_(std::move(sig)) {}

  inoutput_impl() = default;
  inoutput_impl(inoutput_impl&&) = default;
  inoutput_impl& operator=(inoutput_impl&&) = default;
  inoutput_impl(const inoutput_impl&) = delete;
  inoutput_impl& operator=(const inoutput_impl&) = delete;

  template <typename T>
  inoutput_impl& operator=(inoutput_impl<T>&& x)
  {
    base_t::operator=(std::move(x));
    signal_ = std::move(x.signal_);
    return *this;
  }

  template <typename T>
  inoutput_impl(inoutput_impl<T>&& x)
    : base_t(std::move(x))
    , signal_(std::move(x.signal_))
  {}

  auto get() const
    -> ABL_DECLTYPE_RETURN(signal_->last())

  template <typename T>
  void set(T&& value)
  {
    return signal_->send_up(std::forward<T>(value));
  }
};

} // namespace detail

/*!
 * Provides access to reading and writing values of type `T`.
 * Model of `inoutput_value`.
 * @see `inoutput_value`
 */
template <typename T>
class inoutput : public detail::inoutput_impl<detail::up_down_signal<T> >
{
  using base_t = detail::inoutput_impl<detail::up_down_signal<T> >;
  using base_t::base_t;
};

/*!
 * Creates an inout from another inout value.
 * @see `inoutput<T>`
 */
template <typename InoutT>
auto inout(InoutT&& object)
  -> estd::enable_if_t<
    (Inout_value<InoutT>()),
    detail::inoutput_impl<detail::signal_type_t<InoutT> > >
{
  return detail::access::signal(std::forward<InoutT>(object));
}

} // namespace funken
} // namespace atria
