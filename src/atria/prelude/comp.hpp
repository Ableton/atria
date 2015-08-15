// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/estd/functional.hpp>
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

  template <class ...T>
  auto operator() (T&& ...xs)
    -> ABL_DECLTYPE_RETURN(
      estd::invoke(f, estd::invoke(g, std::forward<T>(xs)...)))
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

/*!
 * Right-to left function composition. Returns an object *g* that
 * composes all the given functions @f$ f_i @f$, such that
 * @f[
 *                g(x) = f_1(f_2(...f_n(x)))
 * @f]
 *
 * Functions are invoked via standard *INVOKE*, allowing to compose
 * function pointers, member functions, etc.
 */
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
