// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

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
    -> ABL_DECLTYPE_RETURN(
      f(g(std::forward<X>(x)), std::forward<Y>(ys)...))
};

template <typename ...Fns>
struct get_composed;

template <typename... Ts>
using get_composed_t = typename get_composed<Ts...>::type;

template <typename F>
struct get_composed<F> {
  using type = F;
};

template <typename F, typename... Fs>
struct get_composed<F, Fs...> {
  using type = composed<F, get_composed_t<Fs...> >;
};

} // namespace detail

//!
// Returns an object *g* that composes all the given functions *f_i*,
// such that:
//                 g(x) = f_1(f_2(...f_n(x)))
//
template <typename F>
auto comp(F&& f) -> F&&
{
  return std::forward<F>(f);
}

template <typename Fn, typename ...Fns>
auto comp(Fn&& f, Fns&& ...fns)
  -> detail::get_composed_t<estd::decay_t<Fn>, estd::decay_t<Fns>...>
{
  using result_t = detail::get_composed_t<
    estd::decay_t<Fn>, estd::decay_t<Fns>...>;
  return result_t { std::forward<Fn>(f), comp(std::forward<Fns>(fns)...)};
}

//!
// Similar to clojure.core/identity
//
constexpr struct identity_t
{
  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<ArgT>(x))
} identity {};

//!
// @see constantly
//
template <typename T>
struct constantly_t
{
  T value;

  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) & -> T& { return value; }
  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) const& -> const T& { return value; }
  template <typename ...ArgTs>
  auto operator() (ArgTs&&...) && -> T&& { return std::move(value); }
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
    -> ABL_DECLTYPE_RETURN(
      std::tuple<>{})

  template <typename InputT>
  constexpr auto operator() (InputT&& in) const
    -> ABL_DECLTYPE_RETURN(
      std::forward<InputT>(in))

  template <typename InputT, typename ...InputTs>
  constexpr auto operator() (InputT&& in, InputTs&& ...ins) const
    -> ABL_DECLTYPE_RETURN(
      std::make_tuple(std::forward<InputT>(in),
                      std::forward<InputTs>(ins)...))
} tuplify {};

template <typename FnT>
struct complement_t
{
  FnT fn;

  template <typename... ArgTs>
  auto operator() (ArgTs&& ...args)
    -> ABL_DECLTYPE_RETURN(
      fn(std::forward<ArgTs>(args)...))
};

/*!
 * Similar to clojure.core/complement$1
 */
template <typename FnT>
auto complement(FnT&& fn)
  -> complement_t<estd::decay_t<FnT> >
{
  return { std::forward<FnT>(fn) };
}

} // namespace xform
} // namespace atria
