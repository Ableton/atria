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
class inoutput_impl
  : private watchable<estd::Value_type<SignalT> >
{
  template <typename T> friend class inoutput_impl;
  friend class detail::access;

  using base_t = watchable<estd::Value_type<SignalT> >;

  using signal_ptr_t = std::shared_ptr<SignalT>;
  signal_ptr_t signal_;
  const signal_ptr_t& signal() const { return signal_; }

public:
  using value_type = estd::Value_type<SignalT>;

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
