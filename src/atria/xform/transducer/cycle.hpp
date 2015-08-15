// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/xform/detail/empty_transducer_error.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

namespace detail {

struct cycle_rf_gen
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
      -> decltype(wrap_state<tag>(
                    step(state_unwrap(s), is..., *std::begin(range)),
                    std::make_tuple(std::begin(range), std::end(range))))
    {
      using std::get;
      using std::begin;
      using std::end;

      auto data = state_data(std::forward<StateT>(s), [&] {
          auto first = begin(range);
          auto last  = end(range);
          if (first == last)
            throw detail::empty_transducer_error{};
          return std::make_tuple(first, last);
        });

      if (get<0>(data) == get<1>(data))
        get<0>(data) = begin(range);

      return wrap_state<tag>(
        step(state_unwrap(std::forward<StateT>(s)),
             std::forward<InputTs>(is)...,
             *get<0>(data)++),
        std::move(data));
    }
  };
};

} // namespace detail

template <typename T>
using cycle_t = transducer_impl<detail::cycle_rf_gen, T>;

/*!
 * Generator transducer produces the sequence passed as parameter, by
 * cycleating over it.
 */
template <typename InputRangeT>
constexpr auto cycle(InputRangeT&& r)
  -> cycle_t<estd::decay_t<InputRangeT> >
{
  return cycle_t<estd::decay_t<InputRangeT> > {
    std::forward<InputRangeT>(r) };
}

template <typename InputRangeT, typename ...InputRangeTs>
constexpr auto cycle(InputRangeT&& r, InputRangeTs&& ...rs)
  -> ABL_DECLTYPE_RETURN(
    comp(cycle(std::forward<InputRangeT>(r)),
         cycle(std::forward<InputRangeTs>(rs))...))

} // namespace xform
} // namespace atria
