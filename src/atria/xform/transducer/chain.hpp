// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/detail/empty_transducer_error.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/with_state.hpp>
#include <atria/xform/reduce_nested.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/meta/copy_traits.hpp>

namespace atria {
namespace xform {

namespace detail {

struct chainr_rf_gen
{
  struct tag {};

  template <typename ReducingFnT,
            typename InputRangeT>
  struct apply
  {
    ReducingFnT step;
    InputRangeT range;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state<tag>(step(state_unwrap(s), is...), *this))
    {
      auto data = state_data(std::forward<StateT>(s), constantly(*this));
      return wrap_state<tag>(
        data.step(state_unwrap(std::forward<StateT>(s)),
                  std::forward<InputTs>(is)...),
        std::move(data));
    }
  };

  template <typename T>
  friend auto state_wrapper_complete(tag, T&& wrapper)
    -> ABL_DECLTYPE_RETURN(
      state_complete(
        reduce_nested(
          state_wrapper_data(std::forward<T>(wrapper)).step,
          state_unwrap(std::forward<T>(wrapper)),
          state_wrapper_data(std::forward<T>(wrapper)).range)))
};

} // namespace detail

template <typename T>
using chainr_t = transducer_impl<detail::chainr_rf_gen, T>;

/*!
 * Transducer produces the sequence passed as parameter after all
 * other input has finished.
 */
template <typename InputRangeT>
constexpr auto chainr(InputRangeT&& r)
  -> chainr_t<estd::decay_t<InputRangeT> >
{
  return chainr_t<estd::decay_t<InputRangeT> > {
    std::forward<InputRangeT>(r) };
}

template <typename InputRangeT, typename ...InputRangeTs>
constexpr auto chainr(InputRangeT&& r, InputRangeTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(chainr(std::forward<InputRangeT>(r)),
         chainr(std::forward<InputRangeTs>(rs))...))

/*!
 * Alias for `chainr`
 * @see chainr
 */
template <typename ...InputRangeTs>
constexpr auto chain(InputRangeTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    chainr(std::forward<InputRangeTs>(rs)...))

namespace detail {

struct chainl_rf_gen
{
  template <typename ReducingFnT,
            typename InputRangeT>
  struct apply
  {
    ReducingFnT step;
    InputRangeT range;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), is...)))
    {
      using std::begin;
      using std::end;

      using result_t   = decltype(wrap_state(step(state_unwrap(s), is...)));
      using complete_t = decltype(state_complete(s));

      using wrapped_t   = meta::copy_decay_t<StateT, estd::decay_t<result_t>>;
      using unwrapped_t = meta::copy_decay_t<StateT, estd::decay_t<complete_t>>;

      return with_state(
        std::forward<StateT>(s),
        [&] (unwrapped_t&& st) {
          return wrap_state(
            begin(range) != end(range)
            ? step(reduce_nested_non_empty(
                     step, std::forward<unwrapped_t>(st), range),
                   std::forward<InputTs>(is)...)
            : step(std::forward<unwrapped_t>(st),
                   std::forward<InputTs>(is)...));
        },
        [&] (wrapped_t&& st) {
          return wrap_state(
            step(state_unwrap(std::forward<wrapped_t>(st)),
                 std::forward<InputTs>(is)...));
        });
    }
  };
};

} // namespace detail

template <typename T>
using chainl_t = transducer_impl<detail::chainl_rf_gen, T>;

/*!
 * Transducer produces the sequence passed as parameter before
 * processing the first input.
 */
template <typename InputRangeT>
constexpr auto chainl(InputRangeT&& r)
  -> chainl_t<estd::decay_t<InputRangeT> >
{
  return chainl_t<estd::decay_t<InputRangeT> > {
    std::forward<InputRangeT>(r) };
}

template <typename InputRangeT, typename ...InputRangeTs>
constexpr auto chainl(InputRangeT&& r, InputRangeTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(chainl(std::forward<InputRangeT>(r)),
         chainl(std::forward<InputRangeTs>(rs))...))

} // namespace xform
} // namespace atria
