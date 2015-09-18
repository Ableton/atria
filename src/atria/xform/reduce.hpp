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

#include <atria/xform/detail/reduce_nested_non_empty.hpp>
#include <atria/xform/detail/is_non_empty.hpp>
#include <atria/xform/state_traits.hpp>

namespace atria {
namespace xform {

/*!
 * Similar to clojure.core/reduce.  Unlike `std::accumulate`, this
 * reduces over a range (doesn't take to distinct iterators) and can
 * reduce over several ranges at the same time.  It also supports
 * early termination for transducers.
 *
 * @note Reduce assumes that the ranges that are passed actually hold
 *       the values.  When the ranges are pased as r-values, the
 *       elements will be moved from the range into the reducing
 *       function.  Extra care has to be taken when using range
 *       adaptors or views -- if the adapted container needs to be
 *       used after the reduction, make sure to pass the view as an
 *       l-value, by giving it a name.  Example:
 *
 *       @code{.cpp}
 *           using namespace boost::range::adaptors;
 *           auto x = std::vector<std::string>{ "foo", ... };
 *           reduce(..., x | reversed);
 *           std::cout << x[0] << std::endl; // ooops!
 *       @endcode
 *
 *       One should instead:
 *
 *       @code{.cpp}
 *           using namespace boost::range::adaptors;
 *           auto x = std::vector<std::string>{ "foo", ... };
 *           auto y = x | reversed;
 *           reduce(..., y);
 *           std::cout << x[0] << std::endl; // ooops!
 *       @endcode
 */
template <typename ReducingFnT,
          typename StateT,
          typename ...InputRangeTs>
auto reduce(ReducingFnT&& step, StateT&& state, InputRangeTs&& ...ranges)
  -> estd::decay_t<StateT>
{
  return detail::is_non_empty(ranges...)
    ? state_complete(
      detail::reduce_nested_non_empty(
        std::forward<ReducingFnT>(step),
        std::forward<StateT>(state),
        std::forward<InputRangeTs>(ranges)...))
    : std::forward<StateT>(state);
}

} // namespace xform
} // namespace atria
