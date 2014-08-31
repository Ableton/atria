// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/funken/detail/Signals.hpp>
#include <ableton/funken/detail/Access.hpp>
#include <ableton/funken/detail/Watchable.hpp>
#include <ableton/funken/Concepts.hpp>

namespace ableton {
namespace funken {

namespace detail {

template <typename SignalT>
class InImpl
  : private Watchable<estd::Value_type<SignalT> >
{
  template <typename T> friend class InImpl;
  friend class detail::Access;

  using BaseT = Watchable<estd::Value_type<SignalT> >;
  using SignalPtrT = std::shared_ptr<SignalT>;

  SignalPtrT mpSignal;
  const SignalPtrT& signal() const { return mpSignal; };

public:
  using value_type = estd::Value_type<SignalT>;

  InImpl() = default;
  InImpl(InImpl&&) = default;
  InImpl& operator=(InImpl&&) = default;
  InImpl(const InImpl&) = delete;
  InImpl& operator=(const InImpl&) = delete;

  template <typename T>
  InImpl& operator=(InImpl<T>&& x)
  {
    BaseT::operator=(std::move(x));
    mpSignal = std::move(x.mpSignal);
    return *this;
  }

  template <typename T>
  InImpl(InImpl<T>&& x)
    : BaseT(std::move(x))
    , mpSignal(std::move(x.mpSignal))
  {}

  InImpl(SignalPtrT sig)
    : mpSignal(std::move(sig)) {};

  auto get() const
    -> decltype(mpSignal->last())
  {
    return mpSignal->last();
  }
};

} // namespace detail

//!
// Provides access to reading values of type `T`.
// Model of `In_value`.
// @see `In_value`
//
template <typename T>
class In : public detail::InImpl<detail::DownSignal<T> >
{
  using BaseT = detail::InImpl<detail::DownSignal<T> >;
public:
  using BaseT::BaseT;
  using BaseT::operator=;
};

//!
// Creates an in from another in value.
// @see `In<T>`
//
template <typename InT>
auto in(InT&& object)
  -> estd::enable_if_t<
    (In_value<InT>()),
    detail::InImpl<detail::SignalType_t<InT> > >
{
  return detail::Access::signal(std::forward<InT>(object));
}

} // namespace funken
} // namespace ableton
