// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <iterator>

namespace atria {
namespace xform {
namespace detail {

inline bool is_non_empty()
{
  return true;
}

template <typename RangeT, typename ...RangeTs>
bool is_non_empty(const RangeT& r, const RangeTs& ...rs)
{
  using std::begin;
  using std::end;
  return begin(r) != end(r) && is_non_empty(rs...);
}

} // namespace detail
} // namespace xform
} // namespace atria
