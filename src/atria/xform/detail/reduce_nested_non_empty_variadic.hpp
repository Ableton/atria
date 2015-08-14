// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <iterator>
#include <tuple>
#include <atria/xform/state_traits.hpp>
#include <atria/estd/utility.hpp>

namespace atria {
namespace xform {
namespace detail {

template <std::size_t Index, std::size_t Max>
struct tuple_all_neq_t
{
  template <typename Tuple1T, typename Tuple2T>
  bool operator()(Tuple1T&& t1, Tuple2T&& t2)
  {
    return
      std::get<Index>(std::forward<Tuple1T>(t1)) !=
      std::get<Index>(std::forward<Tuple2T>(t2)) &&
      tuple_all_neq_t<Index + 1, Max>{} (
        std::forward<Tuple1T>(t1),
        std::forward<Tuple2T>(t2));
  }
};

template <std::size_t Max>
struct tuple_all_neq_t<Max, Max>
{
  template <typename Tuple1T, typename Tuple2T>
  bool operator()(Tuple1T&&, Tuple2T&&)
  {
    return true;
  }
};

template <typename Tuple1T, typename Tuple2T>
bool tuple_all_neq(Tuple1T&& t1, Tuple2T&& t2)
{
  constexpr auto size1 = std::tuple_size<estd::decay_t<Tuple1T> >{};
  constexpr auto size2 = std::tuple_size<estd::decay_t<Tuple2T> >{};
  static_assert(size1 == size2, "");

  using impl_t = tuple_all_neq_t<0u, (size1 > size2 ? size2 : size1)>;

  return impl_t{} (
    std::forward<Tuple1T>(t1),
    std::forward<Tuple2T>(t2));
}

template <typename ReducingFnT,
          typename StateT,
          std::size_t ...Indices,
          typename ...InputRangeTs>
auto reduce_nested_non_empty_variadic_impl(estd::index_sequence<Indices...>,
                                           ReducingFnT&& step,
                                           StateT&& initial,
                                           InputRangeTs&& ...ranges)
  -> estd::decay_t<decltype(step(initial, *std::begin(ranges)...))>
{
  auto firsts = std::make_tuple(std::begin(ranges)...);
  auto lasts  = std::make_tuple(std::end(ranges)...);
  auto state  = step(std::forward<StateT>(initial),
                     *std::get<Indices>(firsts)...);

  meta::noop(++std::get<Indices>(firsts)...);
  while (!state_is_reduced(state) && detail::tuple_all_neq(firsts, lasts)) {
    auto new_state = step(std::move(state), *std::get<Indices>(firsts)...);
    state = std::move(new_state);
    meta::noop(++std::get<Indices>(firsts)...);
  }

  return state;
}

template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce_nested_non_empty_variadic(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_variadic_impl(
      estd::make_index_sequence<sizeof...(InputRangeTs)> {},
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeTs>(ranges)...))

} // namespace detail
} // namespace xform
} // namespace atria
