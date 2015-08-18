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

#include <atria/xform/state_traits.hpp>
#include <atria/estd/utility.hpp>

#include <ableton/build_system/Warnings.hpp>

#include <exception>
#include <utility>

namespace atria {
namespace xform {
namespace impure {

struct reduce_aborted_error_base : std::exception
{
  const char* what() const noexcept override;
};

/*!
 * Thrown by an *impure transducer* transducer when it is done and it
 * should terminate early.  It holds the *completed* result of the
 * reduction.
 *
 * @see abort_reduce
  */
template <typename T>
struct reduce_aborted_error : reduce_aborted_error_base
{
  T result;

  template <typename ...Ts>
  reduce_aborted_error(Ts... ts)
    : result{std::move(ts)...}
  {}
};

/*!
 * Throws an @reduce_aborted_error holding @a state.  Note that @a
 * state does not need to be completed before `abort_reduce`.
 *
 * @see reduce_aborted_error
  */
template <typename StateT>
void abort_reduce(StateT&& state)
{
  using complete_t = estd::decay_t<decltype(state_complete(state))>;
  throw reduce_aborted_error<complete_t> {
    state_complete(std::forward<StateT>(state))
  };
}

/*!
 * Like the unary version, but the result type is that of:
 *   `step(state, ins...)`
 *
 * Useful when defining a transducer as a conditional expression, as in:
 *   `whatever ? step(state, ins...) : abort_reduce(step, state, ins...)`
 */
template <typename ReducingFnT, typename StateT, typename ...InputTs>
auto abort_reduce(ReducingFnT&& step, StateT&& state, InputTs&& ...ins)
  -> decltype(step(state, ins...))
{
  using complete_t = estd::decay_t<decltype(state_complete(state))>;
  throw reduce_aborted_error<complete_t> {
    state_complete(std::forward<StateT>(state))
  };
}

} // namespace impure
} // namespace xform
} // namespace atria
