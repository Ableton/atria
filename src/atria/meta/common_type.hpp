// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/utils.hpp>
#include <atria/meta/pack.hpp>
#include <atria/estd/type_traits.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/identity.hpp>
ABL_RESTORE_WARNINGS
#include <type_traits>
#include <utility>

namespace atria {
namespace meta {

/// It is allowed to alias boost::mpl inside atria::meta.
namespace mpl = boost::mpl;

//!
// Result of `CommonType` when no common type exists for types `Ts`
//
template <typename ...Ts>
struct could_not_find_common_type
{
  template <typename T>
  could_not_find_common_type(T&&) {}
  could_not_find_common_type(from_void&&) {}
};

namespace detail {

//!
// Removes r-value reference from type T if is not present in any of
// the types in `OrigT`.  This allows to remove unexpected r-references
// from a type that were added because of the use of `declval`.
//
template<class ValT, class ...OrigTs>
struct undeclval
  : mpl::eval_if<mpl::and_<std::is_rvalue_reference<ValT>,
                           mpl::not_<std::is_rvalue_reference<OrigTs> >... >,
                 std::remove_reference<ValT>,
                 mpl::identity<ValT> >
{};

template <typename T, typename U, typename Enable=void>
struct common_type2
{
  using type = could_not_find_common_type<T, U>;
};

template <typename T, typename U>
struct common_type2<
  T, U,
  estd::void_t<decltype(
    true ? std::declval<T>() : std::declval<U>())>>
{
  using type = typename undeclval<
    decltype(true ? std::declval<T>() : std::declval<U>()),
    T, U
  >::type;
};

} // namespace detail

//!
// Similar to `std::common_type` but addresses several issues.  First,
// on Clang 3.4, `common_type` fails for `void`, where it should not.
// Also, the standard common type removes qualification, which we want
// to preserve. Also, `common_type` is SFINAE-friendly only in new
// versions of GCC.
//
// This implementation preserves qualification when possible, and also
// is total. When no common type is found, it returns the special type
// `CouldNotFindCommonType`, which can be instantiated and converted
// from anything.  This makes it easier to write functions that return
// a common-type of other types, but that might be used in expressions
// where the return type is to be discarded.  This erroneous type was
// chosen instead of `void` to make debugging easier.
//
template <typename... Ts>
struct common_type;

template <typename T, typename ...Ts>
struct common_type<T, Ts...>
  : mpl::fold<pack<Ts...>, T, detail::common_type2<mpl::_1, mpl::_2> >
{};

template <>
struct common_type<>
{
  using type = could_not_find_common_type<>;
};

//!
// C++14 style alias
//
template <typename ...Ts>
using common_type_t = typename common_type<Ts...>::type;

} // namespace meta
} // namespace atria
