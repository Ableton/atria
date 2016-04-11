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
#include <atria/meta/utils.hpp>

namespace atria {
namespace xform {
namespace impure {

namespace detail {

struct enumerate_rf_gen
{
  template <typename ReducingFnT, typename CountT>
  struct apply
  {
    ReducingFnT step;
    CountT count;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
          step(std::forward<StateT>(s),
               count++,
               std::forward<InputTs>(is)...))
  };
};

} // namespace detail

template <typename T>
using enumerate_t = transducer_impl<detail::enumerate_rf_gen, T>;

template <typename IntegralT>
constexpr auto enumerate_from(IntegralT&& init)
  -> enumerate_t<estd::decay_t<IntegralT> >
{
  return enumerate_t<estd::decay_t<IntegralT> > {
    std::forward<IntegralT>(init) };
}

extern const enumerate_t<std::size_t> enumerate;

} // namespace impure
} // namespace xform
} // namespace atria
