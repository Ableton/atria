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
class InoutImpl
  : private watchable<estd::Value_type<SignalT> >
{
  template <typename T> friend class InoutImpl;
  friend class detail::access;

  using BaseT = watchable<estd::Value_type<SignalT> >;

  using SignalPtrT = std::shared_ptr<SignalT>;
  SignalPtrT mpSignal;
  const SignalPtrT& signal() const { return mpSignal; }

public:
  using value_type = estd::Value_type<SignalT>;

  InoutImpl(SignalPtrT sig)
    : mpSignal(std::move(sig)) {}

  InoutImpl() = default;
  InoutImpl(InoutImpl&&) = default;
  InoutImpl& operator=(InoutImpl&&) = default;
  InoutImpl(const InoutImpl&) = delete;
  InoutImpl& operator=(const InoutImpl&) = delete;

  template <typename T>
  InoutImpl& operator=(InoutImpl<T>&& x)
  {
    BaseT::operator=(std::move(x));
    mpSignal = std::move(x.mpSignal);
    return *this;
  }

  template <typename T>
  InoutImpl(InoutImpl<T>&& x)
    : BaseT(std::move(x))
    , mpSignal(std::move(x.mpSignal))
  {}

  auto get() const
    -> decltype(mpSignal->last())
  {
    return mpSignal->last();
  }

  template <typename T>
  void set(T&& value)
  {
    return mpSignal->send_up(std::forward<T>(value));
  }
};

} // namespace detail

//!
// Provides access to reading and writing values of type `T`.
// Model of `Inout_value`.
// @see `Inout_value`
//
template <typename T>
class Inout : public detail::InoutImpl<detail::up_down_signal<T> >
{
  using BaseT = detail::InoutImpl<detail::up_down_signal<T> >;
  using BaseT::BaseT;
};

//!
// Creates an inout from another inout value.
// @see `Inout<T>`
//
template <typename InoutT>
auto inout(InoutT&& object)
  -> estd::enable_if_t<
    (Inout_value<InoutT>()),
    detail::InoutImpl<detail::signal_type_t<InoutT> > >
{
  return detail::access::signal(std::forward<InoutT>(object));
}

} // namespace funken
} // namespace atria
