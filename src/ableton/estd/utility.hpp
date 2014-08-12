// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <utility>

namespace ableton {
namespace estd {

template <typename T, T ...Ints>
struct integer_sequence
{
  using value_type = T;
  static constexpr std::size_t size()
  {
    return sizeof...(Ints);
  }
};

template<std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

namespace detail {

template <typename T, T Curr, T Limit, typename Accum>
struct make_integer_sequence;

template <typename T, T Limit, T ...Ns>
struct make_integer_sequence<T, Limit, Limit, integer_sequence<T, Ns...>>
{
  using type = integer_sequence<T, Ns...>;
};

template <typename T, T Curr, T Limit, T ...Ns>
struct make_integer_sequence<T, Curr, Limit, integer_sequence<T, Ns...>>
  : make_integer_sequence<
      T, (Curr + 1), Limit, integer_sequence<T, Ns..., Curr>
    >
{};

} // namespace detail

template<class T, T N>
using make_integer_sequence = typename detail::make_integer_sequence<
  T, 0, N, integer_sequence<T> >::type;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

} // namespace estd
} // namespace ableton
