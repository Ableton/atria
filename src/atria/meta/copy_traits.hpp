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

#include <atria/estd/type_traits.hpp>
#include <atria/meta/eval.hpp>

namespace atria {
namespace meta {

/*!
 * Metafunction that given a metafunction `TraitChekMf` to check
 * whether a type has a trait, and another `TraitAddMf` to add it to a
 * type, returns `TraitAddMf<DestT>` if `TraitCheckMf<OrigT>`, else
 * `OrigT`.
 */
template <template<typename> class TraitCheckMF,
          template<typename> class TraitAddMf,
          typename OrigT,
          typename DestT>
struct copy_trait
  : std::conditional<
      TraitCheckMF<OrigT>::value,
      typename TraitAddMf<DestT>::type,
      DestT>
{};

#define ABL_DEFINE_COPY_STD_TRAIT(name__)       \
  template <typename OrigT, typename DestT>     \
  struct copy_ ## name__                        \
    : copy_trait<::std::is_ ## name__,          \
                 ::std::add_ ## name__,         \
                 OrigT,                         \
                 DestT>                         \
  {};                                           \
  ABL_METAFUNCTION_T(copy_ ## name__);          \
  /**/

ABL_DEFINE_COPY_STD_TRAIT(lvalue_reference);
ABL_DEFINE_COPY_STD_TRAIT(rvalue_reference);
ABL_DEFINE_COPY_STD_TRAIT(volatile);
ABL_DEFINE_COPY_STD_TRAIT(const);

template <typename OrigT, typename DestT>
struct copy_cv
  : copy_const<OrigT, copy_volatile_t<OrigT, DestT> >
{};
ABL_METAFUNCTION_T(copy_cv);

template <typename OrigT, typename DestT>
struct copy_reference
  : copy_lvalue_reference<OrigT, copy_rvalue_reference_t<OrigT, DestT> >
{};
ABL_METAFUNCTION_T(copy_reference);

/*!
 * Adds reference and cv-qualifications from `OrigT` to `DestT`.  In
 * spite of the name, `is_same<copy_decay<T, decay_t<T>>, T>::value`
 * is not true for every possible `T`, since rules about extent and
 * function decay can not be unambiguously inversed.
 */
template <typename OrigT, typename DestT>
struct copy_decay
  : copy_reference<OrigT, copy_cv_t<estd::remove_reference_t<OrigT>, DestT> >
{};
ABL_METAFUNCTION_T(copy_decay);

} // namespace atria
} // namespace atria
