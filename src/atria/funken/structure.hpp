// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/operators.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/include/out.hpp>
ABL_RESTORE_WARNINGS
#include <atomic>
#include <functional>
#include <iosfwd>

namespace atria {
namespace funken {

namespace detail {

//! Similar to boost::hash_value
template <typename T>
std::size_t hash_value(const T& v)
{
  return std::hash<T>{}(v);
}

//! Similar to boost::hash_combine
template <typename T>
void hash_combine(std::size_t& seed, const T& v)
{
  seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct hash_combine_fn
{
  template <typename T>
  std::size_t operator()(std::size_t seed, const T& v) const
  {
    hash_combine(seed, v);
    return seed;
  }
};

struct first_equal_to_second
{
  template <typename T>
  bool operator()(const T& x) const
  {
    using namespace boost::fusion;
    return at_c<0>(x) == at_c<1>(x);
  }
};

} // namespace detail

//!
// @todo doc
//
template <typename T>
struct structure
  : boost::equality_comparable<structure<T> >
  , boost::less_than_comparable<structure<T> >
{
  structure() = default;
  structure(structure&& x) = default;
  structure(const structure& x) = default;
  structure& operator=(structure&& x) = default;
  structure& operator=(const structure& x) = default;


  std::size_t hash() const
  {
    // Assume computed hash is never 0, I'm not sure this holds... in
    // Clojure they do this sometimes with Murmur3, please research
    // this. Otherwise, I just feel sorry for you if your hash is 0 :)
    if (mHash)
    {
      return mHash;
    }
    else
    {
      using namespace boost::fusion;
      auto hash = fold(self(), 0, detail::hash_combine_fn{});
      mHash = hash;
      return hash;
    }
  }

  void modified()
  {
    mHash = 0;
  }

  const T& self() const { return *static_cast<const T*>(this); }
  T& self() { return *static_cast<const T*>(this); }

private:
  mutable std::size_t mHash = 0;
};

template <typename T>
bool operator==(const structure<T>& a, const structure<T>& b)
{
  if (&a == &b)
    return true;
  if (a.hash() != b.hash())
    return false;
  return boost::fusion::equal_to(a.self(), b.self());
}

template <typename T>
bool operator<(const structure<T>& a, const structure<T>& b)
{
  return boost::fusion::less(a.self(), b.self());
}

template <typename T>
auto operator<<(std::ostream& os, const T& x)
  -> estd::enable_if_t<std::is_convertible<T&, structure<T>&>::value,
                       std::ostream&>
{
  os << typeid(x).name();
  boost::fusion::out(os, x);
  return os;
}

//!
// Call this on an `structure` value to indicate that is has indeed
// changed, invalidating its cached values.
//
template <typename T>
auto modified(T&)
  -> estd::enable_if_t<!std::is_convertible<T&, structure<T>& >::value>
{}

template <typename T>
void modified(structure<T>& x)
{
  x.modified();
}

} // namespace funken
} // namespace atria

namespace std {

template <typename T>
struct hash<atria::funken::structure<T> >
{
  std::size_t operator()(const atria::funken::structure<T>& v) const
  {
    return v.hash();
  }
};

} // namespace std

#define ABL_FUNKEN_STRUCT(structure_full_name, structure_members)       \
  BOOST_FUSION_ADAPT_STRUCT(structure_full_name, structure_members)     \
  namespace std {                                                       \
    template<>                                                          \
    struct hash<structure_full_name>                                    \
      : hash<atria::funken::structure<structure_full_name> >            \
    {};                                                                 \
  } /* namespace std */                                                 \
/**/
