// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/type_traits.hpp>

namespace atria {
namespace funken {

namespace detail {

//!
// Provides access to the underlying signals of different
// entities. This encapsulates acess to the implementation of
// signal-based objects: don't make access to signals public, instead
// friend this class.
//
class Access
{
public:

  //! Returns a smart pointer to the underlying root signal or signals
  //! of an object, if exist.
  template<typename T>
  static auto roots(T&& object) -> decltype(object.roots())
  {
    return object.roots();
  }

  //! Returns a pointer to th underlying signal of an object, if
  //! exists.
  template<typename T>
  static auto signal(T&& object) -> decltype(object.signal())
  {
    return object.signal();
  }

  //! Returns a a optional boost.signal to the specific watchers of
  //! the underlying signal of an object.
  template<typename T>
  static auto watchers(T&& object) -> decltype(object.watchers())
  {
    return object.watchers();
  }
};

//!
// Returns the signal type for an object
//
template <typename ObjectT>
struct SignalType
{
  using type =
    estd::decay_t<
      typename estd::decay_t<decltype(
        Access::signal(std::declval<ObjectT>())
      )>::element_type
    >;
};

template <typename ObjectT>
using SignalType_t = typename SignalType<ObjectT>::type;

} // namespace detail

} // namespace funken
} // namespace atria
