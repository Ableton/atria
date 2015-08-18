//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/tuplify.hpp>
#include <atria/meta/utils.hpp>
#include <functional>

namespace atria {
namespace xform {

namespace detail {

template <typename TableT>
struct lookup_or_key
{
  TableT table;

  template <typename KeyT>
  auto operator() (const KeyT& k) -> const KeyT&
  {
    auto elem = table.find(k);
    return elem == table.end() ? k : elem->second;
  }

  template <typename K1T, typename K2T, typename... KTs>
  auto operator() (K1T&& k1, K2T&& k2, KTs&&... ks)
    -> std::tuple<estd::decay_t<K1T>,
                  estd::decay_t<K2T>,
                  estd::decay_t<KTs>...>
  {
    auto key = std::make_tuple(std::forward<K1T>(k1),
                               std::forward<K2T>(k2),
                               std::forward<KTs>(ks)...);
    auto elem = table.find(key);
    return elem == table.end() ? key : elem->second;
  }
};

template <typename TableT>
struct lookup_default
{
  TableT table;

  template <typename... KeyTs>
  auto operator() (KeyTs&& ...ks)
  -> ABL_DECLTYPE_RETURN(
    table[tuplify(std::forward<KeyTs>(ks)...)])
};

template <typename TableT>
struct lookup_safe
{
  TableT table;

  template <typename... KeyTs>
  auto operator() (KeyTs&& ...ks)
  -> ABL_DECLTYPE_RETURN(
    table.at(tuplify(std::forward<KeyTs>(ks)...)))
};

} // namespace detail

/*!
 * Similar to clojure.core/replace$1
 */
template <typename TableT>
auto replace(TableT&& table)
  -> ABL_DECLTYPE_RETURN(
    map(detail::lookup_or_key<estd::decay_t<TableT> >{ table }))

/*!
 * Transducer that replaces all elements by `table[tuplify(inputs)]`
 */
template <typename TableT>
auto replace_all(TableT&& table)
  -> ABL_DECLTYPE_RETURN(
    map(detail::lookup_default<estd::decay_t<TableT> >{ table }))

/*!
 * Transducer that replaces all elements by `table.at(tuplify(inputs))`
 */
template <typename TableT>
auto replace_all_safe(TableT&& table)
  -> ABL_DECLTYPE_RETURN(
    map(detail::lookup_safe<estd::decay_t<TableT> >{ table }))

} // namespace xform
} // namespace atria
