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
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>

namespace atria {
namespace xform {

namespace detail {

struct repeat_rf_gen
{
  template <typename ReducingFnT,
            typename ValueT>
  struct apply
  {
    ReducingFnT step;
    ValueT value;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        step(std::forward<StateT>(s), std::forward<InputTs>(is)..., value))
  };
};

} // namespace detail

template <typename T>
using repeat_t = transducer_impl<detail::repeat_rf_gen, T>;

/*!
 * Generator transducer produces the value passed as parameter
 * infinitely.
 */
template <typename ValueT>
constexpr auto repeat(ValueT&& r)
  -> repeat_t<estd::decay_t<ValueT> >
{
  return repeat_t<estd::decay_t<ValueT> > {
    std::forward<ValueT>(r) };
}

/*!
 * Generator transducer produces the values passed as parameter
 * up to `n` times.
 */
template <typename IntegralT, typename ValueT>
constexpr auto repeatn(IntegralT&& n, ValueT&& r)
  -> ABL_DECLTYPE_RETURN(
    comp(repeat(std::forward<ValueT>(r)),
         take(std::forward<IntegralT>(n))))

} // namespace xform
} // namespace atria
