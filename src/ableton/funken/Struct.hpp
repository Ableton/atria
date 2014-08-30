// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <ableton/estd/type_traits.hpp>
#include <boost/operators.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/include/out.hpp>
#include <atomic>
#include <functional>
#include <iosfwd>

namespace ableton {
namespace funken {

namespace detail {

//! Similar to boost::hash_value
template <typename T>
std::size_t hashValue(const T& v)
{
  return std::hash<T>{}(v);
}

//! Similar to boost::hash_combine
template <typename T>
void hashCombine(std::size_t& seed, const T& v)
{
  seed ^= hashValue(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct HashCombine
{
  template <typename T>
  std::size_t operator()(std::size_t seed, const T& v) const
  {
    hashCombine(seed, v);
    return seed;
  }
};

struct FirstEqualToSecond
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
struct Struct
  : boost::equality_comparable<Struct<T> >
  , boost::less_than_comparable<Struct<T> >
{
  Struct() = default;
  Struct(Struct&& x) = default;
  Struct(const Struct& x) = default;
  Struct& operator=(Struct&& x) = default;
  Struct& operator=(const Struct& x) = default;


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
      auto hash = fold(self(), 0, detail::HashCombine{});
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
bool operator==(const Struct<T>& a, const Struct<T>& b)
{
  if (&a == &b)
    return true;
  if (a.hash() != b.hash())
    return false;
  return boost::fusion::equal_to(a.self(), b.self());
}

template <typename T>
bool operator<(const Struct<T>& a, const Struct<T>& b)
{
  return boost::fusion::less(a.self(), b.self());
}

template <typename T>
auto operator<<(std::ostream& os, const T& x)
  -> estd::enable_if_t<std::is_convertible<T&, Struct<T>&>::value,
                       std::ostream&>
{
  os << typeid(x).name();
  boost::fusion::out(os, x);
  return os;
};

//!
// Call this on an `Struct` value to indicate that is has indeed
// changed, invalidating its cached values.
//
template <typename T>
auto modified(T&)
  -> estd::enable_if_t<!std::is_convertible<T&, Struct<T>& >::value>
{}

template <typename T>
void modified(Struct<T>& x)
{
  x.modified();
}

} // namespace funken
} // namespace ableton

namespace std {

template <typename T>
struct hash<ableton::funken::Struct<T> >
{
  std::size_t operator()(const ableton::funken::Struct<T>& v) const
  {
    return v.hash();
  }
};

} // namespace std

#define ABL_FUNKEN_STRUCT(StructFullName, StructMembers)                \
  BOOST_FUSION_ADAPT_STRUCT(StructFullName, StructMembers);             \
  namespace std {                                                       \
  template<>                                                            \
  struct hash<StructFullName>                                           \
    : hash<ableton::funken::Struct<StructFullName> >                    \
  {};                                                                   \
  } /* namespace std */                                                 \
/**/
