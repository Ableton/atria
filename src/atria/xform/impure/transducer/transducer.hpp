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

#include <atria/meta/pack.hpp>
#include <atria/xform/any_state.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/prelude/comp.hpp>
#include <functional>

namespace atria {
namespace xform {
namespace impure {

namespace detail {

template <typename... OutputTs>
struct transducer_rf_gen
{
  template <typename StateT>
  struct from_any_state_rf_gen
  {
    template <typename ReducingFnT>
    struct apply
    {
      ReducingFnT step;

      template <typename ...InputTs>
      any_state operator() (any_state s, InputTs&& ...is)
      {
        auto next = step(std::move(s).as<StateT>(),
                         std::forward<InputTs>(is)...);
        s = std::move(next);
        return s;
      }
    };
  };

  template <typename StateT>
  using from_any_state = transducer_impl<from_any_state_rf_gen<StateT> >;

  template <typename ReducingFnT,
            typename XformT>
  struct apply
  {
    ReducingFnT step;
    XformT xform;

    apply(ReducingFnT step_, XformT xform_)
      : step(std::move(step_)), xform(std::move(xform_)) {}

    using xformed_t = typename XformT::result_type;
    xformed_t xformed = {};

    template <typename StateT, typename... InputTs>
    auto operator() (StateT&& s, InputTs&& ...ins)
      -> estd::enable_if_t<
      !std::is_same<estd::decay_t<StateT>, any_state>::value,
        any_state>
    {
      xformed = comp(xform, from_any_state<StateT>{})(step);
      return xformed(std::forward<StateT>(s), std::forward<InputTs>(ins)...);
    }

    template <typename StateT, typename... InputTs>
    auto operator() (StateT&& s, InputTs&& ...ins)
      -> estd::enable_if_t<
      std::is_same<estd::decay_t<StateT>, any_state>::value,
        any_state>
    {
      return xformed(std::forward<StateT>(s), std::forward<InputTs>(ins)...);
    }
  };
};

template <typename... ArgTs>
struct reducing_function
{
  using type = std::function<any_state(any_state, ArgTs...)>;
};

template <typename InputT, typename OutputT>
using transducer_function_t = std::function<
  meta::unpack_t<reducing_function, InputT> (
    meta::unpack_t<reducing_function, OutputT>)>;

} // namespace detail

template <typename InputT, typename OutputT=InputT>
using transducer = transducer_impl<
  meta::unpack<detail::transducer_rf_gen, OutputT>,
  detail::transducer_function_t<InputT, OutputT> >;

} // namespace impure
} // namespace xform
} // namespace atria
