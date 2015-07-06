// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>
#include <atria/funken/concepts.hpp>

namespace atria {
namespace funken {

namespace detail {

template <typename SignalT>
class input_impl
  : private watchable<estd::Value_type<SignalT> >
{
  template <typename T> friend class input_impl;
  friend class detail::access;

  using base_t = watchable<estd::Value_type<SignalT> >;
  using signal_ptr_t = std::shared_ptr<SignalT>;

  signal_ptr_t signal_;
  const signal_ptr_t& signal() const { return signal_; }

public:
  using value_type = estd::Value_type<SignalT>;

  input_impl() = default;
  input_impl(input_impl&&) = default;
  input_impl& operator=(input_impl&&) = default;
  input_impl(const input_impl&) = delete;
  input_impl& operator=(const input_impl&) = delete;

  template <typename T>
  input_impl& operator=(input_impl<T>&& x)
  {
    base_t::operator=(std::move(x));
    signal_ = std::move(x.signal_);
    return *this;
  }

  template <typename T>
  input_impl(input_impl<T>&& x)
    : base_t(std::move(x))
    , signal_(std::move(x.signal_))
  {}

  input_impl(signal_ptr_t sig)
    : signal_(std::move(sig)) {}

  auto get() const
    -> ABL_AUTO_RETURN(signal_->last())
};

} // namespace detail

//!
// Provides access to reading values of type `T`.
// Model of `Input_value`.
// @see `Input_value`
//
template <typename T>
class input : public detail::input_impl<detail::down_signal<T> >
{
  using base_t = detail::input_impl<detail::down_signal<T> >;
public:
  using base_t::base_t;
  using base_t::operator=;
};

//!
// Creates an in from another in value.
// @see `input<T>`
//
template <typename InT>
auto in(InT&& object)
  -> estd::enable_if_t<
    (In_value<InT>()),
    detail::input_impl<detail::signal_type_t<InT> > >
{
  return detail::access::signal(std::forward<InT>(object));
}

} // namespace funken
} // namespace atria
