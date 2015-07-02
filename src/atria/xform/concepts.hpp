// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/concept.hpp>
#include <atria/xform/functional.hpp>
#include <atria/xform/reducers.hpp>
#include <atria/xform/state.hpp>

#include <boost/mpl/eval_if.hpp>

namespace atria {
namespace xform {

ABL_CONCEPT_SPEC(State)
{
  template <typename T>
  auto requires_(T&& t)
    -> decltype(
      meta::expressions(
        state_unwrap(t),
        state_complete(t),
        bool(state_is_reduced(t)),
        int(state_data(t, constantly(0))),
        meta::require_any<
          decltype(state_unwrap(t)),
          std::is_same<T, boost::mpl::_>,
          meta::models_<State_spec, boost::mpl::_> >()));
};

ABL_CONCEPT_SPEC(Reducer)
{
  template <typename R, typename S, typename... Is>
  auto requires_(R&& r, S&& s, Is&&... is)
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

ABL_CONCEPT_SPEC(Transducer)
{
  template <typename T>
  auto requires_(T&& t)
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
