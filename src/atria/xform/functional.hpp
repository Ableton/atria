// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>

#include <ableton/build_system/Warnings.hpp>
#include <tuple>

namespace atria {
namespace xform {

namespace detail {

template <class F, class G>
struct composed
{
  F f;
  G g;

  template <class X, class ...Y >
  auto operator() (X&& x, Y&& ...ys)
    -> decltype(f(g(std::forward<X>(x)), std::forward<Y>(ys)...))
  {
    return f(g(std::forward<X>(x)), std::forward<Y>(ys)...);
  }
};

} // namespace detail

//!
// Returns an object *g* that composes all the given functions *f_i*,
// such that:
//                 g(x) = f_1(f_2(...f_n(x)))
//
template <typename F>
auto comp(F&& f)
  -> F&&
{
  return std::forward<F>(f);
}

template <typename Fn, typename ...Fns>
auto comp(Fn&& f, Fns&& ...fns)
  -> detail::composed<
  estd::decay_t<Fn>,
  estd::decay_t<decltype(comp(std::forward<Fns>(fns)...))>>
{
  using result_t = detail::composed<
    estd::decay_t<Fn>,
    estd::decay_t<decltype(comp(std::forward<Fns>(fns)...))>>;
  return result_t { std::forward<Fn>(f), comp(std::forward<Fns>(fns)...)};
}

//!
// Similar to clojure.core/identity
//
constexpr struct identity_t
{
  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const -> ArgT&&
  {
    return std::forward<ArgT>(x);
  }
} identity {};

//!
// @see constantly
//
template <typename T>
struct constantly_t
{
  using result_type = const T&;
  T value;

  template <typename ArgT>
  constexpr auto operator() (ArgT&&) const
    -> result_type
  {
    return value;
  }
};

//!
// Similar to clojure.core/constantly
//
template <typename T>
auto constantly(T&& value)
  -> constantly_t<estd::decay_t<T> >
{
  return constantly_t<estd::decay_t<T> >{ std::forward<T>(value) };
}

//!
// Function that forwards its argument if only one element passed,
// otherwise it makes a tuple.
//
constexpr struct tuplify_t
{
  constexpr auto operator() () const
    -> std::tuple<>
  {
    return std::tuple<>{};
  }

  template <typename InputT>
  constexpr auto operator() (InputT&& in) const -> InputT&&
  {
    return std::forward<InputT>(in);
  }

  template <typename InputT, typename ...InputTs>
  constexpr auto operator() (InputT&& in, InputTs&& ...ins) const
    -> decltype(std::make_tuple(std::forward<InputT>(in),
                                std::forward<InputTs>(ins)...))
  {
    return std::make_tuple(std::forward<InputT>(in),
                           std::forward<InputTs>(ins)...);
  }
} tuplify {};

} // namespace xform
} // namespace atria
