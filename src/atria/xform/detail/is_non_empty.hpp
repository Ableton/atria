// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <iterator>

namespace atria {
namespace xform {
namespace detail {

template <typename RangeT>
bool is_non_empty(const RangeT& r)
{
  using std::begin;
  using std::end;
  return begin(r) != end(r);
}

template <typename RangeT, typename ...RangeTs>
bool is_non_empty(const RangeT& r, const RangeTs& ...rs)
{
  return is_non_empty(r) && is_non_empty(rs...);
}

} // namespace detail
} // namespace xform
} // namespace atria
