// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/funken/detail/signals.hpp>
#include <atria/funken/detail/access.hpp>
#include <atria/funken/detail/watchable.hpp>
#include <atria/funken/Concepts.hpp>

namespace atria {
namespace funken {

namespace detail {

template <typename SignalT>
class OutImpl
{
  template <typename T> friend class OutImpl;
  friend class detail::access;

  using SignalPtrT = std::shared_ptr<SignalT>;
  SignalPtrT mpSignal;
  const SignalPtrT& signal() const { return mpSignal; }

public:
  using value_type = estd::Value_type<SignalT>;

  OutImpl() = default;
  OutImpl(OutImpl&&) = default;
  OutImpl& operator=(OutImpl&&) = default;
  OutImpl(const OutImpl&) = delete;
  OutImpl& operator=(const OutImpl&) = delete;

  template <typename T>
  OutImpl& operator=(OutImpl<T>&& x)
  {
    mpSignal = std::move(x.mpSignal);
    return *this;
  }

  template <typename T>
  OutImpl(OutImpl<T>&& x)
    : mpSignal(std::move(x.mpSignal))
  {}

  OutImpl(SignalPtrT sig)
    : mpSignal(std::move(sig)) {}

  template <typename T>
  void set(T&& value)
  {
    return mpSignal->send_up(std::forward<T>(value));
  }
};

} // namespace detail

//!
// Provides access to writing values of type `T`.
// Model of `Input_value`.
// @see `Input_value`
//
template <typename T>
class Out : public detail::OutImpl<detail::up_down_signal<T> >
{
  using BaseT = detail::OutImpl<detail::up_down_signal<T> >;
public:
  using BaseT::BaseT;
  using BaseT::operator=;
};

//!
// Creates an out from another out value.
// @see `Out<T>`
//
template <typename OutT>
auto out(OutT&& object)
  -> estd::enable_if_t<
    (Out_value<OutT>()),
    detail::OutImpl<detail::signal_type_t<OutT> > >
{
  return detail::access::signal(std::forward<OutT>(object));
}

} // namespace funken
} // namespace atria
