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

#include <iterator>

#include <atria/xform/config.hpp>
#include <atria/xform/detail/reduce_nested_non_empty_variadic.hpp>
#include <atria/xform/detail/reduce_nested_non_empty_nullary.hpp>

#if   ABL_REDUCE_TAIL_RECURSIVE
#  include <atria/xform/detail/reduce_nested_non_empty_tail_recursive.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_tail_recursive

#elif ABL_REDUCE_WITH_ACCUMULATE
#  include <atria/xform/detail/reduce_nested_non_empty_tail_accumulate.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_accumulate

#elif ABL_REDUCE_ALWAYS_VARIADIC
#  include <atria/xform/detail/reduce_nested_non_empty_variadic.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_variadic

#else
#  include <atria/xform/detail/reduce_nested_non_empty_non_variadic.hpp>
#  define ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL \
  ::atria::xform::detail::reduce_nested_non_empty_non_variadic
#endif

namespace atria {
namespace xform {
namespace detail {

template <typename ReducingFnT,
          typename StateT>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_nullary(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state)))

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state,
                             InputRangeT&& range)
  -> ABL_DECLTYPE_RETURN(
    ABL_REDUCE_NESTED_NON_EMPTY_NON_VARIADIC_IMPL(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeT>(range)))

template <typename ReducingFnT,
          typename StateT,
          typename InputRangeT,
          typename ...InputRangeTs>
auto reduce_nested_non_empty(ReducingFnT&& step,
                             StateT&& state,
                             InputRangeT&& range,
                             InputRangeTs&& ...ranges)
  -> ABL_DECLTYPE_RETURN(
    reduce_nested_non_empty_variadic(
      std::forward<ReducingFnT>(step),
      std::forward<StateT>(state),
      std::forward<InputRangeT>(range),
      std::forward<InputRangeTs>(ranges)...))

} // namespace detail
} // namespace xform
} // namespace atria
