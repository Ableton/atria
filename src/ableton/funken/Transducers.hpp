// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/estd/type_traits.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/reverse_fold.hpp>
#include <tuple>

namespace ableton {
namespace funken {

namespace detail {

struct ComposedReducer
{
  template <typename State, typename Fn>
  auto operator()(State&& state, Fn&& next)
    -> decltype(std::forward<Fn>(next)(std::forward<State>(state)))
  {
    return std::forward<Fn>(next)(std::forward<State>(state));
  }
};

template<typename Fn, typename ...Fns>
struct Composed : std::tuple<Fn, Fns...>
{
  using std::tuple<Fn, Fns...>::tuple;

  std::tuple<Fn, Fns...>& asTuple() { return *this; }
  const std::tuple<Fn, Fns...>& asTuple() const { return *this; }

  template <typename Arg>
  auto operator() (Arg&& arg) const
    -> decltype(boost::fusion::reverse_fold(
                  asTuple(), arg, ComposedReducer{}))
  {
    return boost::fusion::reverse_fold(
      asTuple(), arg, ComposedReducer{});
  }
};

} // namespace detail

//!
// Returns an object *g* that composes all the given functions *f_i*,
// such that:
//                 g(x) = f_1(f_2(...f_n(x)))
//
template <typename Fn, typename ...Fns>
detail::Composed<Fn, Fns...> comp(Fn&& fn, Fns&& ...fns)
{
  return { std::forward<Fn>(fn), std::forward<Fns>(fns)... };
};

} // namespace funken
} // namespace ableton
