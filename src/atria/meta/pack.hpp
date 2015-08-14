// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
ABL_RESTORE_WARNINGS
#include <type_traits>

namespace atria {
namespace meta {

/*!
 * MPL-compatible sequence that just holds a vector of types as a
 * paremeter pack.
 */
template <typename ...Ts>
struct pack
{
};

namespace detail {

template <template<typename...> class MF, typename ArgT>
struct unpack
{
  using type = MF<ArgT>;
};

template <template<typename...> class MF, typename... ArgTs>
struct unpack<MF, meta::pack<ArgTs...> >
{
  using type = MF<ArgTs...>;
};

} // namespace detail

/*!
 * Metafunction that given a variadic template `MF` and a type `ArgT`,
 * returns `MF<ArgT>`, or if ArgT is of the form `pack<Args...>` then
 * returns `MF<Args...>`.
 */
template <template<typename...> class MF, typename T>
using unpack = typename detail::unpack<MF, T>::type;

template <template<typename...> class MF, typename T>
using unpack_t = typename unpack<MF, T>::type;

struct pack_tag;

template <class ... Args>
struct pack_iterator;

template <class ... Args>
struct pack_iterator<atria::meta::pack<Args...>>
{
  typedef atria::meta::pack_tag tag;
  typedef boost::mpl::forward_iterator_tag category;
};

} // namespace meta
} // namespace atria

namespace boost {
namespace mpl {

template <class ... Args>
struct sequence_tag<atria::meta::pack<Args...>>
{
  typedef atria::meta::pack_tag type;
};

template <>
struct front_impl<atria::meta::pack_tag>
{
  template <typename PackT> struct apply;
  template <typename T, typename ...Ts>
  struct apply<atria::meta::pack<T, Ts...>>
  {
    using type = T;
  };
};

template <>
struct empty_impl<atria::meta::pack_tag>
{
  template <typename PackT> struct apply;
  template <typename ...Ts>
  struct apply<atria::meta::pack<Ts...>>
    : std::integral_constant<bool, sizeof...(Ts) == 0>
  {};
};

template <>
struct pop_front_impl<atria::meta::pack_tag>
{
  template <typename PackT> struct apply;
  template <class First, class ...Types>
  struct apply<atria::meta::pack<First, Types...>>
  {
    typedef atria::meta::pack<Types...> type;
  };
};

template <>
struct push_front_impl<atria::meta::pack_tag>
{
  template <typename PackT, typename T> struct apply;
  template <typename T, typename ... Args>
  struct apply<atria::meta::pack<Args...>, T>
  {
    typedef atria::meta::pack<T, Args...> type;
  };
};

template <>
struct push_back_impl<atria::meta::pack_tag>
{
  template <typename PackT, typename T> struct apply;
  template <typename T, typename ... Args >
  struct apply<atria::meta::pack<Args...>, T>
  {
    typedef atria::meta::pack<Args..., T> type;
  };
};

template <>
struct size_impl<atria::meta::pack_tag>
{
  template <typename PackT> struct apply;
  template <typename ...Ts>
  struct apply<atria::meta::pack<Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)>
  {};
};

template <>
struct at_impl<atria::meta::pack_tag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct back_impl<atria::meta::pack_tag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct clear_impl<atria::meta::pack_tag>
{
  template <typename PackT>
  struct apply
  {
    typedef atria::meta::pack<> type;
  };
};

template <>
struct pop_back_impl<atria::meta::pack_tag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct begin_impl<atria::meta::pack_tag>
{
  template <class PackT> struct apply
  {
    typedef atria::meta::pack_iterator<PackT> type;
  };
};

template <>
struct end_impl<atria::meta::pack_tag>
{
  template <typename> struct apply
  {
    typedef atria::meta::pack_iterator<
      atria::meta::pack<>> type;
  };
};

template <typename First, class ... Args>
struct deref<atria::meta::pack_iterator<
  atria::meta::pack<First, Args...>>>
{
  typedef First type;
};

template <typename First, class ... Args>
struct next<atria::meta::pack_iterator<
  atria::meta::pack<First, Args...>>>
{
  typedef atria::meta::pack_iterator<
    atria::meta::pack<Args...>> type;
};

} // namespace mpl
} // namespace boost
