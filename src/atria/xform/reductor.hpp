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

#include <atria/xform/skip.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace xform {

/*!
 * Common reductor interface.  This is an abstract type, use @a
 * `reductor_fn` and @a `empty_reductor_fn` concrete types.
 *
 * @see reductor_fn
 * @see empty_reductor_fn
 */
template <typename ReducingFnT,
          typename StateT,
          typename... InputTs>
struct reductor_fn_base
{
  using reducing_fn_type = ReducingFnT;
  using state_type = StateT;
  using complete_type = estd::decay_t<
    decltype(state_complete(std::declval<state_type>()))>;

  reductor_fn_base() = delete;

  /*!
   * Returns whether the reductor_fn will produce more values.
   */
  explicit operator bool() const
    { return !state_is_reduced(state_); }

  /*!
   * Completes and returns the state of the reduction.  The operation
   * os move aware.
   */
  complete_type complete() const&
  { return state_complete(state_); }

  complete_type complete() &&
  { return state_complete(std::move(state_)); }

  /*!
   * Peeks at the current visible state of the reduction.  The operation is
   * move aware.  If an argument is passed, it updates the current state.
   */
  complete_type current() const&
  { return state_unwrap_all(state_); }

  complete_type current() &&
  { return state_unwrap_all(std::move(state_)); }

  template <typename T>
  void current(T&& x)
  { state_ = state_rewrap(std::move(state_), std::forward<T>(x)); }

  /*!
   * Evaluates the next step of the reduction, passing the inputs @a
   * `ins` to the reducing function.
   *
   * @note When operated on a `const` object, the it returns a new
   *       reductor_fn object.  Otherwise, the operation is performed
   *       in-place and the object itself is returned.  The operation
   *       is move-aware.
   */
  template <typename... InputTs2>
  reductor_fn_base& operator() (InputTs2&& ...ins) &
  {
    auto next = step_(std::move(state_), std::forward<InputTs2>(ins)...);
    state_ = std::move(next);
    return *this;
  }

  template <typename... InputTs2>
  reductor_fn_base operator() (InputTs2&& ...ins) const&
  {
    auto copied = *this;
    copied(std::forward<InputTs2>(ins)...);
    return copied;
  }

  template <typename... InputTs2>
  reductor_fn_base&& operator() (InputTs2&& ...ins) &&
  {
    return std::move((*this)(std::forward<InputTs2>(ins)...));
  }

protected:
  template <typename ReducingFnT2,
            typename StateT2>
  reductor_fn_base(ReducingFnT2&& step,
                   StateT2&& state)
    : step_(std::forward<ReducingFnT2>(step))
    , state_(std::forward<StateT2>(state))
  {}

private:
  reducing_fn_type step_;
  state_type state_;
};

/*!
 * Function object that performs a reduction using a reducing function
 * of type `ReducingFnT`, an initial state of type of type
 * `InitialStateT` and inputs of types `InputTs...`.
 *
 * The function object can be called with arguments converibles to
 * `InputTs...` to step the reduction.  If the reductor_fn object is
 * `const`, it will return a new value representing the advanced
 * state.  Otherwise it performs the reduction in place and returns a
 * reference to itself. See @a `reductor_fn_base` for details on the
 * interface.
 *
 * This object requires an initial input to be pased to the
 * constructor.  If no input is available at construction time, use @a
 * `empty_reductor_fn` instead.
 */
template <typename ReducingFnT,
          typename InitialStateT,
          typename... InputTs>
struct reductor_fn : reductor_fn_base<
  ReducingFnT,
  estd::result_of_t<ReducingFnT(InitialStateT, InputTs...)>,
  InputTs...>
{
  using base_t = reductor_fn_base<
    ReducingFnT,
    estd::result_of_t<ReducingFnT(InitialStateT, InputTs...)>,
    InputTs...>;

  template <typename ReducingFnT2,
            typename InitialStateT2,
            typename... InputTs2>
  reductor_fn(ReducingFnT2&& step,
              InitialStateT2&& state,
              InputTs2&& ...ins)
    : base_t(std::forward<ReducingFnT2>(step),
             step(std::forward<InitialStateT2>(state),
                  std::forward<InputTs2>(ins)...))
  {}
};

/*!
 * Constructs a @a `reductor_fn` object with deduced argument types.
 */
template <typename ReducingFnT, typename InitialStateT, typename... InputTs>
auto reductor(ReducingFnT&& step, InitialStateT&& state, InputTs&& ...ins)
  -> reductor_fn<estd::decay_t<ReducingFnT>,
                 estd::decay_t<InitialStateT>,
                 estd::decay_t<InputTs>... >
{
  return {
    std::forward<ReducingFnT>(step),
    std::forward<InitialStateT>(state),
    std::forward<InputTs>(ins)...
  };
}

namespace detail {

template <typename ReducingFnT>
struct caller
{
  ReducingFnT step;

  template <typename... Args>
  auto operator() (Args&& ...args)
  -> ABL_DECLTYPE_RETURN(
    call(step, std::forward<Args>(args)...))
};

} // namespace detail

/*!
 * Reductor_Fn object that does not require inputs to be fed at
 * construction time.  In some cases though, @a `reductor_fn` can perform
 * better.
 *
 * @see reductor_fn
 * @see reductor_fn_base
 */
template <typename ReducingFnT,
          typename InitialStateT,
          typename... InputTs>
struct empty_reductor_fn : reductor_fn_base<
  detail::caller<estd::decay_t<ReducingFnT>>,
  estd::decay_t<skip_result_t<ReducingFnT, InitialStateT, InputTs...> >,
  InputTs...>
{
  using base_t = reductor_fn_base<
    detail::caller<estd::decay_t<ReducingFnT> >,
    estd::decay_t<skip_result_t<ReducingFnT, InitialStateT, InputTs...> >,
    InputTs...>;

  template <typename ReducingFnT2,
            typename InitialStateT2,
            typename... InputTs2>
  empty_reductor_fn(ReducingFnT2&& step,
                    InitialStateT2&& state)
    : base_t(detail::caller<estd::decay_t<ReducingFnT>> {
               std::forward<ReducingFnT2>(step) },
             typename base_t::state_type {
               std::forward<InitialStateT2>(state) })
  {}
};

/*!
 * Constructs an @a `empty_reductor_fn` object with deduced argument
 * types.  The `InputTs` over which the reductor_fn functions have to be
 * passed explicitly though.
 */
template <typename... InputTs, typename ReducingFnT, typename InitialStateT>
auto empty_reductor(ReducingFnT&& step, InitialStateT&& state)
  -> empty_reductor_fn<estd::decay_t<ReducingFnT>,
                       estd::decay_t<InitialStateT>,
                       estd::decay_t<InputTs>... >
{
  return {
    std::forward<ReducingFnT>(step),
    std::forward<InitialStateT>(state)
  };
}

} // namespace xform
} // namespace atria
