// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/meta/copy_traits.hpp>
#include <atria/meta/pack.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/mpl/transform.hpp>
ABL_RESTORE_WARNINGS

namespace atria {
namespace variant {

namespace detail {

template <typename T, typename Enable=void>
struct variant_types_aux {};

template <typename T>
struct variant_types_aux<T, estd::void_t<typename T::variant_types> >
{
  using type = typename T::variant_types;
};

} // namespace detail

/*!
 * Given an unqualified variant type `T`, returns a `meta::pack` with
 * the alternatives in the variant.  Specialize to customize the
 * result of `variant_types`.
 */
template <typename T>
struct variant_types_impl
  : detail::variant_types_aux<T>
{};

template <typename... Ts>
struct variant_types_impl<meta::pack<Ts...> >
{
  using type = meta::pack<Ts...>;
};

/*!
 * Metafunction that for a given type `T`, returns a `meta::pack`
 * containing the list of types that can be held in the variant.  If
 * `T` is qualified (e.g. `const&`) the qualification is copied into
 * the types returned.
 *
 * By default, this metafunction just accesses
 * `decay_t<T>::variant_types` to get the list of unqualified types.
 * A type might alternatively specialize `variant_types_impl<T>` to
 * override this behaviour.
 */
template <typename T>
struct variant_types
  : boost::mpl::transform<
     typename variant_types_impl<estd::decay_t<T> >::type,
     meta::copy_decay<T, boost::mpl::_1 > >
{};
ABL_METAFUNCTION_T(variant_types);

} // namespace variant
} // namespace atria
