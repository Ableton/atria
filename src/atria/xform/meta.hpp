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

#include <atria/xform/into.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/meta/utils.hpp>
#include <atria/meta/eval.hpp>

namespace atria {
namespace xform {

namespace detail {

struct output_of_rf_t
{
  template <typename StateT, typename ...InputTs>
  constexpr auto operator() (StateT, InputTs&&...) const
    -> meta::pack<InputTs&&...>;
};

} // namespace detail

/*!
 * Metafunction that given a transducer @a `XformT` and some inputs @a
 * `InputTs`, returns the type of the outputs of the transducer,
 * wrapped in a `meta::pack`.  It preserves reference types.
 */
template <typename XformT, typename... InputTs>
struct output_of
{
  using type = decltype(
    state_complete(
      std::declval<XformT>()(detail::output_of_rf_t{})(
        std::declval<meta::bottom>(),
        std::declval<InputTs>()...)));
};
ABL_METAFUNCTION_T(output_of);

/*!
 * Metafunction that given a transducer @a `XformT` and some inputs @a
 * `InputTs`, returns the type of the output of the transducer,
 * combined as combined in a single result with `tuplify`.
 *
 * @see tuplify
 */
template <typename XformT, typename... InputTs>
struct result_of
{
  using type = estd::decay_t<decltype(
    state_complete(
      std::declval<XformT>()(last_rf)(
        std::declval<meta::bottom>(),
        std::declval<InputTs>()...)))>;
};
ABL_METAFUNCTION_T(result_of);

} // namespace xform
} // namespace atria
