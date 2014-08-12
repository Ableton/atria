// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/estd/type_traits.hpp>
#include <memory>

namespace ableton {
namespace estd {

template <class T, class ...Args>
auto make_unique(Args&& ...args)
  -> estd::enable_if_t<!std::is_array<T>::value,
                       std::unique_ptr<T> >
{
  return std::unique_ptr<T> {
    new T(std::forward<Args>(args)...) };
}

template <class T>
auto make_unique(std::size_t size)
  -> estd::enable_if_t<std::is_array<T>::value,
                       std::unique_ptr<T> >
{
  return std::unique_ptr<T> {
    new typename std::remove_extent<T>::type[size]() };
}

} // namespace estd
} // namespace ableton
