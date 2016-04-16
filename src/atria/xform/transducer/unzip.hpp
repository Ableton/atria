//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer_impl.hpp>
#include <atria/meta/get_index_sequence.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace xform {

namespace detail {

using std::get;

template <typename ResultT, typename ...Ts>
struct unzip_types_aux;

template <typename ResultT>
struct unzip_types_aux<ResultT>
{
  using type = ResultT;
};

template <typename... ResultTs, typename T, typename... Ts>
struct unzip_types_aux<meta::pack<ResultTs...>, T, Ts...>
  : unzip_types_aux<meta::pack<ResultTs...>,
                    meta::pack<T, meta::get_index_sequence<T> >,
                    Ts...>
{};

template <typename... ResultTs,
          typename T, std::size_t... Indexes,
          typename... Ts>
struct unzip_types_aux<meta::pack<ResultTs...>,
                       meta::pack<T, estd::index_sequence<Indexes...> >,
                       Ts...>
  : unzip_types_aux<meta::pack<ResultTs...,
                               decltype(get<Indexes>(std::declval<T>()))...>,
                    Ts...>
{};

template <typename... ResultTs, typename T, typename... Ts>
struct unzip_types_aux<meta::pack<ResultTs...>,
                       meta::pack<T, meta::could_not_get_index_sequence>,
                       Ts...>
  : unzip_types_aux<meta::pack<ResultTs..., T>, Ts...>
{};

/*!
 * Metafunction that given some types `Ts...`, returns a `meta::pack`
 * containing, from every type `T`:
 *
 *   - If `T` supports `get<Index>(declval<T>())`, the expansion of
 *     the result type of such expression for valid indexes.
 *
 *   - Otherwise, `T` itself.
 *
 * @see get_index_sequence
 */
template <typename... Ts>
struct unzip_types : unzip_types_aux<meta::pack<>, Ts...> {};

template <typename... Ts>
using unzip_types_t = typename unzip_types<estd::decay_t<Ts>... >::type;

/*!
 * Metafunction that computes the result of @a unzip for given arguments
 * @see unzip
 */
template <typename ReducingFnT, typename StateT, typename... InputTs>
struct unzip_result
{
  template <typename... Ts>
  struct apply : std::result_of<ReducingFnT(StateT, Ts...)> {};

  using type = meta::unpack_t<apply, unzip_types_t<InputTs...> >;
};

template <typename ReducingFnT, typename StateT, typename... InputTs>
using unzip_result_t =
  typename unzip_result<ReducingFnT, StateT, InputTs...>::type;

struct unzip_rf_gen
{
  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    struct last_input_tag {};

    template <typename ResultT, std::size_t... Indexes,
              typename StateT, typename InputT, typename... InputTs>
    auto impl_apply(meta::pack<ResultT> r, estd::index_sequence<Indexes...>,
                    StateT&& s, InputT&& i, InputTs&& ...is)
      -> ResultT
    {
      return impl(r,
                  std::forward<StateT>(s),
                  std::forward<InputTs>(is)...,
                  std::get<Indexes>(std::forward<InputT>(i))...);
    }

    template <typename ResultT,
              typename StateT, typename InputT, typename... InputTs>
    auto impl_apply(meta::pack<ResultT> r, meta::could_not_get_index_sequence,
                    StateT&& s, InputT&& i, InputTs&& ...is)
      -> ResultT
    {
      return impl(r,
                  std::forward<StateT>(s),
                  std::forward<InputTs>(is)...,
                  std::forward<InputT>(i));
    }

    template <typename ResultT, typename StateT, typename InputT, typename... InputTs>
    auto impl(meta::pack<ResultT>, StateT&& s, InputT&&, InputTs&& ...is)
      -> estd::enable_if_t<
      std::is_same<estd::decay_t<InputT>, last_input_tag>::value,
        ResultT>
    {
      return step(std::forward<StateT>(s),
                  std::forward<InputTs>(is)...);
    }

    template <typename ResultT, typename StateT, typename InputT, typename... InputTs>
    auto impl(meta::pack<ResultT> r, StateT&& s, InputT&& i, InputTs&& ...is)
      -> estd::enable_if_t<
      !std::is_same<estd::decay_t<InputT>, last_input_tag>::value,
        ResultT>
    {
      return impl_apply(
        r,
        meta::get_index_sequence<InputT>{},
        std::forward<StateT>(s),
        std::forward<InputT>(i),
        std::forward<InputTs>(is)...);
    }

    template <typename StateT, typename... InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> unzip_result_t<ReducingFnT, StateT, InputTs...>
    {
      return impl(
        meta::pack<unzip_result_t<ReducingFnT, StateT, InputTs...> >{},
        std::forward<StateT>(s),
        std::forward<InputTs>(is)...,
        last_input_tag{});
    }
  };
};

} // namespace detail


using unzip_t = transducer_impl<detail::unzip_rf_gen>;

/*!
 * Transducer that expands all tuples in the inputs in the argument
 * list of the next transducer.
 */
constexpr auto unzip = unzip_t {};

} // namespace xform
} // namespace atria
