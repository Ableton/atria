// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace xform {

//!
// Box for a value that is `finished` reducing. It might be returned
// by reducers that might know that they are done before processing
// all the input, for example, when the state reaches an idempotent
// value.
//
// @see take
//
template <typename T>
struct reduced_t
{
  T value;
};

//!
// Constructs a reduced value for `value`
//
template <typename T>
auto reduced(T&& value) -> reduced_t<estd::decay_t<T> >
{
  return { std::forward<T>(value) };
}

template <typename T>
struct from_reduced_impl : identity_t {};

template <typename T>
struct from_reduced_impl<reduced_t<T>>
{
  template <typename ArgT>
    auto operator() (ArgT&& x) -> decltype(x.value) { return x.value; }
};

//!
// Unwraps the value in a potentially *reduced* box.
// @see reduced_t
// @see maybe_reduced
//
template <typename T>
auto from_reduced(T&& t) ->
  decltype(from_reduced_impl<estd::decay_t<T>>{}(std::forward<T>(t)))
{
  return from_reduced_impl<estd::decay_t<T>>{}(std::forward<T>(t));
}

//!
// Returns whether all values of a type are finished reducing.
// @see reduced_t
//
template <typename T>
struct type_is_reduced : std::false_type {};
template <typename T>
struct type_is_reduced<reduced_t<T>> : std::true_type {};

//!
// Returns whether a value `v` is a finished reduction.
// @see reduced_t
//
template <typename T>
auto is_reduced(const T&)
  -> estd::enable_if_t<!type_is_reduced<T>::value, bool>
{
  return false;
}

template <typename T>
auto is_reduced(const T&)
  -> estd::enable_if_t<type_is_reduced<T>::value, bool>
{
  return true;
}

//!
// Holds a value that may or may not be a finished reduction.  It
// is convertible from any other type that may be reduced.
// @see reduced_t
//
template <typename T>
struct maybe_reduced
{
  bool reduced;
  T value;

  template <typename U>
  maybe_reduced(U x)
    : reduced(is_reduced(x))
    , value(std::move(from_reduced(x)))
  {}
};

template <typename T>
auto is_reduced(const maybe_reduced<T>& v) -> bool { return v.reduced; }

template <typename T>
struct from_reduced_impl<maybe_reduced<T>>
  : from_reduced_impl<reduced_t<T>> {};

} // namespace xform
} // namespace atria
