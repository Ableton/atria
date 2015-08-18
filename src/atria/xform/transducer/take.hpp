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
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/detail/empty_transducer_error.hpp>
#include <atria/prelude/constantly.hpp>

namespace atria {
namespace xform {

namespace detail {

struct take_rf_gen
{
  struct tag {};

  template <typename ReducingFnT,
            typename IntegralT>
  struct apply
  {
    ReducingFnT step;
    IntegralT total;

    struct initial
    {
      apply* this_;
      IntegralT operator() ()
      {
        if (this_->total <= 0)
          throw empty_transducer_error{};
        return this_->total;
      }
    };

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        wrap_state<tag>(
          step(state_unwrap(std::forward<StateT>(s)),
               std::forward<InputTs>(is)...),
          state_data(std::forward<StateT>(s),
                     initial{this}) - 1))
  };

  template <typename T>
  friend bool state_wrapper_data_is_reduced(tag, T&& n)
  {
    return std::forward<T>(n) <= 0;
  }
};

} // namespace detail

template <typename T>
using take_t = transducer_impl<detail::take_rf_gen, T>;

/*!
 * Similar to clojure.core/take$1
 */
template <typename IntegralT>
auto take(IntegralT&& n)
  -> take_t<estd::decay_t<IntegralT> >
{
  return take_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(n) };
}

} // namespace xform
} // namespace atria
