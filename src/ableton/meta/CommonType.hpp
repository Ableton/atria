// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/meta/Utils.hpp>
#include <ableton/meta/Pack.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/identity.hpp>

#include <type_traits>
#include <utility>

namespace ableton {
namespace meta {

/// It is allowed to alias boost::mpl inside ableton::meta.
namespace mpl = boost::mpl;

//!
// Result of `CommonType` when no common type exists for types `Ts`
//
template <typename ...Ts>
struct CouldNotFindCommonType
{
  template <typename T>
  CouldNotFindCommonType(T&&) {};
  CouldNotFindCommonType(FromVoid&&) {};
};

namespace detail {

//!
// Removes r-value reference from type T if is not present in any of
// the types in `OrigT`.  This allows to remove unexpected r-references
// from a type that were added because of the use of `declval`.
//
template<class ValT, class ...OrigTs>
struct Undeclval
  : mpl::eval_if<mpl::and_<std::is_rvalue_reference<ValT>,
                           mpl::not_<std::is_rvalue_reference<OrigTs> >... >,
                 std::remove_reference<ValT>,
                 mpl::identity<ValT> >
{};

template <typename T, typename U, typename Enable=void>
struct CommonType2
{
  using type = CouldNotFindCommonType<T, U>;
};

template <typename T, typename U>
struct CommonType2<
  T, U,
  meta::EnableIfType_t<decltype(
    true ? std::declval<T>() : std::declval<U>())>>
{
  using type = typename Undeclval<
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
template <typename T, typename ...Ts>
struct CommonType
  : mpl::fold<Pack<Ts...>, T, detail::CommonType2<mpl::_1, mpl::_2> >
{};

//!
// C++14 style alias
//
template <typename ...Ts>
using CommonType_t = typename CommonType<Ts...>::type;

} // namespace meta
} // namespace ableton
