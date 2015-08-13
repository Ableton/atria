// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/meta/utils.hpp>
#include <utility>

namespace atria {
namespace prelude {

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

} // namespace prelude

using prelude::comp;

} // namespace atria
