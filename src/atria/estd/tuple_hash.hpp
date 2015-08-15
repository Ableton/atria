// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#include <boost/functional/hash.hpp>
#include <tuple>

namespace std {

template<typename... Ts>
struct hash<tuple<Ts...> >
{
  template <typename T>
  size_t operator()(T&& x) const noexcept
  {
    return boost::hash_value(std::forward<T>(x));
  }
};

} // namespace std
