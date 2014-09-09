// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

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

#include <type_traits>

namespace ableton {
namespace meta {

//!
// MPL-compatible sequence that just holds a vector of types as a
// paremeter pack.
//
template <typename ...Ts>
struct Pack {};

struct PackTag;

template <class ... Args>
struct PackIterator;

template <class ... Args>
struct PackIterator<ableton::meta::Pack<Args...>>
{
  typedef ableton::meta::PackTag tag;
  typedef boost::mpl::forward_iterator_tag category;
};

} // namespace meta
} // namespace ableton

namespace boost {
namespace mpl {

template <class ... Args>
struct sequence_tag<ableton::meta::Pack<Args...>>
{
  typedef ableton::meta::PackTag type;
};

template <>
struct front_impl<ableton::meta::PackTag>
{
  template <typename PackT> struct apply;
  template <typename T, typename ...Ts>
  struct apply<ableton::meta::Pack<T, Ts...>>
  {
    using type = T;
  };
};

template <>
struct empty_impl<ableton::meta::PackTag>
{
  template <typename PackT> struct apply;
  template <typename ...Ts>
  struct apply<ableton::meta::Pack<Ts...>>
    : std::integral_constant<bool, sizeof...(Ts) == 0>
  {};
};

template <>
struct pop_front_impl<ableton::meta::PackTag>
{
  template <typename PackT> struct apply;
  template <class First, class ...Types>
  struct apply<ableton::meta::Pack<First, Types...>>
  {
    typedef ableton::meta::Pack<Types...> type;
  };
};

template <>
struct push_front_impl<ableton::meta::PackTag>
{
  template <typename PackT, typename T> struct apply;
  template <typename T, typename ... Args>
  struct apply<ableton::meta::Pack<Args...>, T>
  {
    typedef ableton::meta::Pack<T, Args...> type;
  };
};

template <>
struct push_back_impl<ableton::meta::PackTag>
{
  template <typename PackT, typename T> struct apply;
  template <typename T, typename ... Args >
  struct apply<ableton::meta::Pack<Args...>, T>
  {
    typedef ableton::meta::Pack<Args..., T> type;
  };
};

template <>
struct size_impl<ableton::meta::PackTag>
{
  template <typename PackT> struct apply;
  template <typename ...Ts>
  struct apply<ableton::meta::Pack<Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)>
  {};
};

template <>
struct at_impl<ableton::meta::PackTag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct back_impl<ableton::meta::PackTag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct clear_impl<ableton::meta::PackTag>
{
  template <typename PackT>
  struct apply
  {
    typedef ableton::meta::Pack<> type;
  };
};

template <>
struct pop_back_impl<ableton::meta::PackTag>
{
  template <typename T>
  struct apply
  {
    static_assert(std::is_same<T, T>::value, "not implemented");
  };
};

template <>
struct begin_impl<ableton::meta::PackTag>
{
  template <class PackT> struct apply
  {
    typedef ableton::meta::PackIterator<PackT> type;
  };
};

template <>
struct end_impl<ableton::meta::PackTag>
{
  template <typename> struct apply
  {
    typedef ableton::meta::PackIterator<
      ableton::meta::Pack<>> type;
  };
};

template <typename First, class ... Args>
struct deref<ableton::meta::PackIterator<
  ableton::meta::Pack<First, Args...>>>
{
  typedef First type;
};

template <typename First, class ... Args>
struct next<ableton::meta::PackIterator<
  ableton::meta::Pack<First, Args...>>>
{
  typedef ableton::meta::PackIterator<
    ableton::meta::Pack<Args...>> type;
};

} // namespace mpl
} // namespace boost
