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

#include <atria/xform/any_state.hpp>
#include <atria/xform/impure/abort_reduce.hpp>
#include <atria/xform/detail/reduce_nested_non_empty.hpp>
#include <atria/xform/detail/is_non_empty.hpp>

namespace atria {
namespace xform {
namespace impure {

namespace detail {

template <typename ResultT, typename ArgT>
auto from_any_state(ArgT&& s)
  -> estd::enable_if_t<std::is_same<estd::decay_t<ArgT>, any_state>::value,
                       estd::decay_t<ResultT> >
{
  return std::forward<ArgT>(s).template as<ResultT>();
}

template <typename ResultT, typename ArgT>
auto from_any_state(ArgT&& s)
  -> estd::enable_if_t<!std::is_same<estd::decay_t<ArgT>, any_state>::value,
                       ArgT&&>
{
  return std::forward<ArgT>(s);
}

} // namespace detail

template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  try {
    return detail::from_any_state<StateT>(
      xform::detail::is_non_empty(ranges...)
        ? state_complete(
          xform::detail::reduce_nested_non_empty(
            std::forward<ReducingFnT>(step),
            std::forward<StateT>(state),
            std::forward<InputRangeTs>(ranges)...))
        : std::forward<StateT>(state));
  } catch (reduce_aborted_error<estd::decay_t<StateT> >& err) {
    return std::move(err.result);
  } catch (reduce_aborted_error<any_state>& err) {
    return std::move(err.result).as<StateT>();
  }
}

} // namespace impure
} // namespace xform
} // namespace atria
