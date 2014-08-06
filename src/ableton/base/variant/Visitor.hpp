// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <boost/variant/static_visitor.hpp>
#include <boost/type_traits.hpp>
#include <cassert>

namespace ableton {
namespace base {
namespace variant {

namespace detail {

//!
// General visitor based on a set of function objects.
//
template <typename ...Fns>
struct VisitorImpl : public Fns...
{
  VisitorImpl(Fns&& ...fns)
    : Fns(std::forward<Fns>(fns))... { }
};

} // namespace detail

//!
// General visitor based on a set of function objects.
//
template <typename ReturnType, typename ...Fns>
struct Visitor : public boost::static_visitor<ReturnType>
{
  Visitor(Fns&& ...fns)
    : mImpl(std::forward<Fns>(fns)...)
  {}

  template<typename T>
  ReturnType operator() (T&& x)
  {
    return mImpl(std::forward<T>(x));
  }

private:
  detail::VisitorImpl<Fns...> mImpl;
};

namespace detail
{
struct Bottom
{
  template <typename T> operator T();
};
} // namespace detail

//!
// Returns a boost variant static_visitor that uses a set of given
// functions to implement it. The return type is inferred from the
// first function passed.
//
template <typename Fn, typename... Fns>
Visitor<typename std::result_of<Fn(detail::Bottom)>::type, Fn, Fns...>
visitor(Fn&& fn, Fns&& ...fns)
{
  return {
    std::forward<Fn>(fn),
    std::forward<Fns>(fns)...
  };
}

} // namespace variant
} // namespace base
} // namespace ableton
