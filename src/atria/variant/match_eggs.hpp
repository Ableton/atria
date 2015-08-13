// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/variant/variant_types_eggs.hpp>
#include <atria/variant/visitor.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <eggs/variant.hpp>
ABL_RESTORE_WARNINGS
#include <utility>

namespace atria {
namespace variant {

namespace detail {

template <typename T>
struct is_eggs_variant : std::is_base_of<
  meta::unpack<eggs::variant, variant_types_t<estd::decay_t<T> > >,
  estd::decay_t<T> >
{};

} // namespace detail

/*!
 * Destructure a `eggs::variant` with a given set of functions.  This
 * uses C++ function overload rules to pick the right function.  If
 * the passed in variant is a non-const l-value, alternatives can
 * destructure by reference and mutate the variant in place.
 *
 * @note This method can destructure either instances of
 *       `eggs::variant<...>` or for subclasses of
 *       `eggs::variant<Ts...>` for which `meta::variant_types` is
 *       defined to return `meta::pack<Ts...>`.
 *
 * @return The return type is deduced as the `meta::common_type<>` of
 *         the result of destructuring all alternatives in the variant.
 */
template <typename VariantT, typename ...FnTs>
auto match(VariantT&& variant, FnTs&& ...fns)
  -> estd::enable_if_t<
  detail::is_eggs_variant<estd::decay_t<VariantT> >{},
    visitor_result_of_t<
      detail::visitor_impl<FnTs...>,
      variant_types_t<VariantT&&> > >
{
  using result_t = visitor_result_of_t<
    detail::visitor_impl<FnTs...>,
    variant_types_t<VariantT&&> >;

  using eggs_t = meta::copy_decay_t<
    VariantT,
    meta::unpack<eggs::variant, variant_types_t<estd::decay_t<VariantT> > > >;

  return eggs::variants::apply<result_t>(
    visitor_for<VariantT>(std::forward<FnTs>(fns)...),
    // eggs::variants::apply is too stupid to detect that a subclass
    // of a variant can be destructured, so we cast up such that
    // subclassing works
    std::forward<eggs_t>(static_cast<eggs_t&&>(variant)));
}

} // namespace variant
} // namespace atria
