// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/meta/eval.hpp>
#include <utility>

namespace atria {
namespace meta {

namespace detail {
struct disabled {};
} // namespace detail

template <bool C, typename T>
struct lazy_enable_if : estd::conditional_t<C, T, detail::disabled> {};

template <bool C, typename T>
using lazy_enable_if_t = meta::eval_t<lazy_enable_if<C, T> >;

} // namespace meta
} // namespace atria
