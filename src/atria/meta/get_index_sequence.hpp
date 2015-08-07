// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/estd/utility.hpp>
#include <tuple>
#include <array>

namespace atria {
namespace meta {

struct could_not_get_index_sequence {};

namespace detail {

using std::get;

template <typename T, typename I, I N,
          typename Enable = void>
struct get_integer_sequence_aux
{
  using type = estd::conditional_t<
    (N == 0),
    could_not_get_index_sequence,
    estd::make_integer_sequence<I, N> >;
};

template <typename T, typename I, I N>
struct get_integer_sequence_aux<
     T, I, N, estd::void_t<decltype(get<N>(std::declval<T>()))> >
  : get_integer_sequence_aux<T, I, N + 1>
{};

template <typename T, typename I>
struct get_integer_sequence
  : get_integer_sequence_aux<T, I, 0>
{};

template <typename ...Ts, typename I>
struct get_integer_sequence<std::tuple<Ts...>, I>
{
  using type = estd::make_integer_sequence<I, sizeof...(Ts)>;
};

template <typename T, typename U, typename I>
struct get_integer_sequence<std::pair<T, U>, I>
{
  using type = estd::make_integer_sequence<I, 2>;
};

template <typename T, std::size_t N, typename I>
struct get_integer_sequence<std::array<T, N>, I>
{
  using type = estd::make_integer_sequence<I, N>;
};

} // namespace detail

template <typename T, typename I>
using get_integer_sequence =
  typename detail::get_integer_sequence<estd::decay_t<T>, I>::type;

template <typename T>
using get_index_sequence = get_integer_sequence<T, std::size_t>;

} // namespace meta
} // namespace atria
