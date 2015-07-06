// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/reduce.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <vector>

namespace atria {
namespace xform {

namespace detail {

struct partition_rf_gen
{
  struct tag {};

  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT size;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(
        wrap_state<partition_rf_gen::tag>(
          step(state_unwrap(s), std::vector<estd::decay_t<decltype(tuplify(is...))>>{}),
          make_tuple(std::vector<estd::decay_t<decltype(tuplify(is...))>>{}, step)))
    {
      using elem_t = estd::decay_t<decltype(tuplify(is...))>;
      auto data = state_data(s, [&] {
          std::vector<elem_t> v;
          v.reserve(size);
          return make_tuple(v, step);
        });
      auto& next = std::get<0>(data);

      next.push_back(tuplify(std::forward<InputTs>(is)...));
      if (next.size() == size) {
        auto ss = step(state_unwrap(std::forward<StateT>(s)), next);
        next.clear();
        return wrap_state<partition_rf_gen::tag> (
          std::move(ss),
          make_tuple(std::move(next), step));
      }
      else {
        return wrap_state<partition_rf_gen::tag> (
          state_unwrap(std::forward<StateT>(s)),
          make_tuple(std::move(next), step));
      }
    }
  };
};

} // namespace detail

template <typename _1, typename _2>
struct state_traits<state_wrapper<detail::partition_rf_gen::tag, _1, _2> >
  : state_traits<state_wrapper<> >
{
  template <typename T>
  static auto complete(T&& wrapper)
    -> decltype(state_complete(state_unwrap(std::forward<T>(wrapper))))
  {
    auto next = std::get<0>(std::get<1>(std::forward<T>(wrapper)));
    auto step = std::get<1>(std::get<1>(std::forward<T>(wrapper)));
    return state_complete(
      next.empty()
      ? state_unwrap(std::forward<T>(wrapper))
      : step(state_unwrap(std::forward<T>(wrapper)),
             std::move(next)));
  }
};

template <typename T>
using partition_t = transducer_impl<detail::partition_rf_gen, T>;

/*!
 * Similar to clojure.core/partition$1
 */
template <typename IntegralT>
auto partition(IntegralT&& n)
  -> partition_t<estd::decay_t<IntegralT> >
{
  return partition_t<estd::decay_t<IntegralT> > { n };
}

} // namespace xform
} // namespace atria
