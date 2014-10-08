// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/estd/type_traits.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/reverse_fold.hpp>
ABL_RESTORE_WARNINGS
#include <tuple>

namespace ableton {
namespace funken {

namespace detail {

struct ComposedReducer
{
  template <typename State, typename Fn>
  auto operator()(State&& state, Fn&& next)
    -> decltype(next(std::forward<State>(state)))
  {
    return next(std::forward<State>(state));
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
auto comp(Fn&& fn, Fns&& ...fns)
  -> detail::Composed<estd::decay_t<Fn>, estd::decay_t<Fns>...>
{
  return { std::forward<Fn>(fn), std::forward<Fns>(fns)... };
}

//!
// Similar to clojure.core/identity
//
constexpr struct Identity
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
struct Constantly
{
  using result_type = const T&;
  T value;

  template <typename ArgT>
  constexpr auto operator() (ArgT&& x) const
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
  -> Constantly<estd::decay_t<T> >
{
  return Constantly<estd::decay_t<T> >{ std::forward<T>(value) };
}

//!
// Function that forwards its argument if only one element passed,
// otherwise it makes a tuple.
//
constexpr struct Tuplify
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

} // namespace funken
} // namespace ableton
