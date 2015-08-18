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
#include <atria/estd/functional.hpp>

namespace atria {
namespace xform {

#if ABL_CXX14

auto map = [](auto mapping) mutable
{
  return [=](auto step) mutable
  {
    return [=](auto&& s, auto&& ...is) mutable
    {
      return step(ABL_FORWARD(s), estd::invoke(mapping, ABL_FORWARD(is)...));
    };
  };
};

#else // ABL_CXX14

namespace detail {

struct map_rf_gen
{
  template <typename ReducingFnT,
            typename MappingT>
  struct apply
  {
    ReducingFnT step;
    MappingT mapping;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        step(std::forward<State>(s),
             estd::invoke(mapping, std::forward<Inputs>(is)...)))
  };
};

} // namespace detail

template <typename T>
using map_t = transducer_impl<detail::map_rf_gen, T>;

/*!
 * Similar to clojure.core/map$1
 */
template <typename MappingT>
auto map(MappingT&& mapping)
  -> map_t<estd::decay_t<MappingT> >
{
  return map_t<estd::decay_t<MappingT> > {
    std::forward<MappingT>(mapping) };
}

#endif // ABL_CXX14

} // namespace xform
} // namespace atria
