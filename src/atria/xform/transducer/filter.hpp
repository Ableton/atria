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
#include <atria/xform/skip.hpp>
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto filter = [](auto predicate) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      return estd::invoke(predicate, is...)
        ? call(step, ABL_FORWARD(s), ABL_FORWARD(is)...)
        : skip(step, ABL_FORWARD(s), ABL_FORWARD(is)...);
    };
  };
};

#else // ABL_CXX14

namespace detail {

struct filter_rf_gen
{
  template <typename ReducingFnT,
            typename PredicateT>
  struct apply
  {
    ReducingFnT step;
    PredicateT predicate;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        estd::invoke(predicate, is...)
          ? call(step, std::forward<State>(s), std::forward<Inputs>(is)...)
          : skip(step, std::forward<State>(s), std::forward<Inputs>(is)...))
  };
};

} // namespace detail

template <typename T>
using filter_t = transducer_impl<detail::filter_rf_gen, T>;

/*!
 * Similar to clojure.core/filter$1
 */
template <typename PredicateT>
auto filter(PredicateT&& predicate)
  -> filter_t<estd::decay_t<PredicateT> >
{
  return filter_t<estd::decay_t<PredicateT> > {
    std::forward<PredicateT>(predicate) };
}

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
