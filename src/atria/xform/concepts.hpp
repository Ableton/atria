// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/concept.hpp>
#include <atria/xform/functional.hpp>
#include <atria/xform/reducers.hpp>
#include <atria/xform/state.hpp>

#include <boost/mpl/eval_if.hpp>

namespace atria {
namespace xform {

template <typename _Arg>
struct State
  : meta::concept<State<_Arg> >
{
  template <typename T>
  auto requires(T&& t)
    -> decltype(
      meta::expressions(
        state_unwrap(t),
        state_complete(t),
        bool(state_is_reduced(t)),
        int(state_data(t, constantly(0))),
        meta::require_any<
          decltype(state_unwrap(t)),
          std::is_same<T, boost::mpl::_>,
          State<boost::mpl::_> >()));
};

template <typename _Arg1, typename _Arg2, typename ..._Args>
struct Reducer
  : meta::concept<Reducer<_Arg1, _Arg2, _Args...> >
{
  template <typename R, typename S, typename... Is>
  auto requires(R&& r, S&& s, Is&&... is)
    -> decltype(
      meta::expressions(
        r(s, is...),
        r(r(s, is...), is...),
        meta::require<(
          std::is_same<
            decltype(r(s, is...)),
            decltype(r(r(s, is...), is...))>())>(),
        meta::require<(
          State<decltype(r(s, is...))>())>(),
        meta::require<(
          State<decltype(r(r(s, is...), is...))>())>()));
};

template <typename _Arg>
struct Transducer
  : meta::concept<Transducer<_Arg> >
{
  template <typename T>
  auto requires(T&& t)
    -> decltype(
      meta::expressions(
        meta::require<(
          Reducer<decltype(t(first_r)), int, int>())>(),
        meta::require<(
          Reducer<decltype(t(first_r)), char*, int>())>(),
        meta::require<(
          Reducer<decltype(t(first_r)), char*, int, float>())>()));
};

} // namespace xform
} // namespace atria
