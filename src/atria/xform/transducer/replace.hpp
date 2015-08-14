// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
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
