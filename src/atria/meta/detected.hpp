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
 * @file Utilities that extend the functionality of `estd::detected_t`
 */

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/meta/utils.hpp>
#include <atria/meta/eval.hpp>

namespace atria {
namespace meta {

/*!
 * Like `estd::detected_or`, but evaluates `D` lazily.
 */
template <typename D, template<class...> class Op, typename T>
struct lazy_detected_or
{
  template <typename X>
  using operation_t = identity<Op<X> >;
  using type = eval_t<estd::detected_or_t<D, operation_t, T> >;
};

template <typename D, template<class...> class Op, typename T>
using lazy_detected_or_t = eval_t<lazy_detected_or<D, Op, T> >;

/*!
 * Metafunction that returns the first type that is detected via the
 * metafunctions in `Ops...`
 */
template <typename T, template<class...> class... Ops>
struct detected_any;

template <typename T,
          template<class...> class Op>
struct detected_any<T, Op>
{
  using type = estd::detected_t<Op, T>;
};

template <typename T,
          template<class...> class Op,
          template<class...> class... Ops>
struct detected_any<T, Op, Ops...>
{
  using type = lazy_detected_or_t<detected_any<T, Ops...>, Op, T>;
};

template <typename T, template<class...> class... Ops>
using detected_any_t = typename detected_any<T, Ops...>::type;

} // namespace meta
} // namespace xform
