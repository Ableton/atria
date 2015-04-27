// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/functional.hpp>
#include <atria/estd/type_traits.hpp>

namespace atria {
namespace xform {

//!
// Exception to be thrown by reducers to signal that they have reached
// an idempotent element.  This idempotent value is exposed in the
// `value` attribute of the exception.  The process running the
// reduction should catch the exception and stop providing input to
// the reducer.
//
template <typename StateT>
struct reduce_finished_exception : std::exception
{
  StateT value;

  reduce_finished_exception(StateT value_)
    : value(std::move(value_)) {}

  const char* what() const noexcept override {
    return "Reduction finished early";
  };
};

//!
// Throws a `reduce_finished_exception` holding value `st`.
//
template <typename StateT>
void reduce_finished(StateT&& st)
{
  throw reduce_finished_exception<estd::decay_t<StateT>> {
    std::forward<StateT>(st)
  };
}

} // namespace xform
} // namespace atria
