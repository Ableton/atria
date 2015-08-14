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
#include <tuple>

namespace atria {
namespace meta {

/*!
 * Sequence tag form std::tuple adaptor for boost::mpl.  This is
 * mostly based on http://stackoverflow.com/a/15865204
 */
struct std_tuple_tag;

template <class ... Args>
struct std_tuple_iterator;

template <class ... Args>
struct std_tuple_iterator<std::tuple<Args...>>
{
  typedef atria::meta::std_tuple_tag tag;
  typedef boost::mpl::forward_iterator_tag category;
};

} // namespace meta
} // namespace atria

namespace boost {
namespace mpl {

template <class ... Args>
struct sequence_tag<std::tuple<Args...>>
{
  typedef atria::meta::std_tuple_tag type;
};

template <>
struct front_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple>
  struct apply
    : std::tuple_element<0, Tuple>
  {
  };
};

template <>
struct empty_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple> struct apply
  : std::integral_constant<bool, std::tuple_size<Tuple>::value == 0>
  {
  };
};

template <>
struct pop_front_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple> struct apply;

  template <class First, class ... Types> struct apply<std::tuple<First, Types...>>
  {
    typedef std::tuple<Types...> type;
  };
};

template <>
struct push_front_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple, typename T> struct apply;

  template <typename T, typename ... Args>
  struct apply<std::tuple<Args...>, T>
  {
    typedef std::tuple<T, Args...> type;
  };
};

template <>
struct push_back_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple, typename T> struct apply;

  template <typename T, typename ... Args >
  struct apply<std::tuple<Args...>, T>
  {
    typedef std::tuple<Args..., T> type;
  };
};


template <>
struct size_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple> struct apply
  : std::tuple_size<Tuple>
  {
  };
};

template <>
struct at_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple, typename N> struct apply
  : std::tuple_element<N::value, Tuple>
  {
  };
};

template <>
struct back_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple> struct apply
  : std::tuple_element<std::tuple_size<Tuple>::value - 1, Tuple>
  {
  };
};

template <>
struct clear_impl<atria::meta::std_tuple_tag>
{
  template <typename Tuple> struct apply
  {
    typedef std::tuple<> type;
  };
};

template <>
struct pop_back_impl<atria::meta::std_tuple_tag>
{
  template <int ...> struct tuple_seq {};
  template <int N, int ...S> struct tuple_gens : tuple_gens<N-1, N-1, S...> {};
  template <int ...S> struct tuple_gens<0, S...>{ typedef tuple_seq<S...> type; };

  template <class Tuple, class Index> struct apply_impl;
  template <class Tuple, int ... S> struct apply_impl<Tuple, tuple_seq<S...>>
  {
    typedef std::tuple<typename std::tuple_element<S, Tuple>::type...> type;
  };

  template <typename Tuple> struct apply : apply_impl<Tuple, typename tuple_gens<std::tuple_size<Tuple>::value - 1>::type> { };
};

template <>
struct begin_impl<atria::meta::std_tuple_tag>
{
  template <class Tuple> struct apply
  {
    typedef atria::meta::std_tuple_iterator<Tuple> type;
  };
};

template <>
struct end_impl<atria::meta::std_tuple_tag>
{
  template <typename> struct apply
  {
    typedef atria::meta::std_tuple_iterator<std::tuple<>> type;
  };
};

template <typename First, class ... Args>
struct deref<atria::meta::std_tuple_iterator<std::tuple<First, Args...>>>
{
  typedef First type;
};

template <typename First, class ... Args>
struct next<atria::meta::std_tuple_iterator<std::tuple<First, Args...>>>
{
  typedef atria::meta::std_tuple_iterator<std::tuple<Args...>> type;
};

} // namespace mpl
} // namespace boost
