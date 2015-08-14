// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
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
