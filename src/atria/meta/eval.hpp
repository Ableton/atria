// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <boost/preprocessor/seq/for_each_i.hpp>

namespace atria {
namespace meta {

/*!
 * Alias to access `typename T::type`
 */
template <typename T>
using eval_t = typename T::type;

/*!
 * Macro to define an evaluated version of a metafunction with `_t`
 * suffix, in the style of the C++14 standard library.
 */
#define ABL_METAFUNCTION_T(name__)                              \
  template <typename... Ts>                                     \
  using name__ ## _t = ::atria::meta::eval_t<name__ <Ts...> >   \
  /**/

#if ABL_CXX14
/*!
 * Alias to access `T::type::value`
 */
template <typename T>
constexpr auto eval_v = T::type::value;

/*!
 * Macro to define an evaluated version of a value-metafunction with
 * `_v` suffix, in the style of the C++14 standard library.
 */
#define ABL_METAFUNCTION_V(name__)                                      \
  template <typename... Ts>                                             \
  constexpr auto name__ ## _v = ::atria::meta::eval_v<name__ <Ts...> >  \
  /**/
#else
#define ABL_METAFUNCTION_V(name__)
#endif // ABL_CXX14

} // namespace meta
} // namespace atria
