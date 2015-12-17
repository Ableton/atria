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

#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/with_state.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/meta/copy_traits.hpp>
#include <functional>
#include <ostream>

namespace atria {
namespace xform {

namespace detail {

struct empty_output {};

template <typename StreamT>
StreamT& operator<< (StreamT& stream, empty_output)
{
  return stream;
}

struct write_rf_gen
{
  template <typename ReducingFnT,
            typename OutputStreamRefT,
            typename InSeparatorT,
            typename ArgSeparatorT>
  struct apply
  {
    ReducingFnT step;
    OutputStreamRefT stream_ref;
    InSeparatorT in_separator;
    ArgSeparatorT arg_separator;

    template <typename OutputStreamT>
    void impl(OutputStreamT&) {}

    template <typename OutputStreamT, typename InputT>
    void impl(OutputStreamT& stream, InputT&& in)
    {
      stream << std::forward<InputT>(in);
    }

    template <typename OutputStreamT, typename InputT, typename... InputTs>
    void impl(OutputStreamT& stream, InputT&& in, InputTs... ins)
    {
      stream << std::forward<InputT>(in)
             << arg_separator;
      impl(stream, std::forward<InputTs>(ins)...);
    }

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(wrap_state(step(state_unwrap(s), is...)))
    {
      using std::begin;
      using std::end;

      using result_t   = decltype(wrap_state(step(state_unwrap(s), is...)));
      using complete_t = decltype(state_complete(s));

      using wrapped_t   = meta::copy_decay_t<StateT, estd::decay_t<result_t>>;
      using unwrapped_t = meta::copy_decay_t<StateT, estd::decay_t<complete_t>>;

      auto& stream = stream_ref.get();
      return with_state(
        std::forward<StateT>(s),
        [&] (unwrapped_t&& st) {
          impl(stream, is...);
          return wrap_state(
            step(std::forward<unwrapped_t>(st),
                 std::forward<InputTs>(is)...));
        },
        [&] (wrapped_t&& st) {
          stream << in_separator;
          impl(stream, is...);
          return wrap_state(
            step(state_unwrap(std::forward<wrapped_t>(st)),
                 std::forward<InputTs>(is)...));
        });
    }
  };
};

} // namespace detail

template <typename OutputStreamRefT, typename InSeparatorT, typename ArgSeparatorT>
using write_t = transducer_impl<detail::write_rf_gen,
                                OutputStreamRefT,
                                InSeparatorT,
                                ArgSeparatorT>;

/*!
 * Transducer that writes the into a given @a `stream` using the
 * `operator <<`.  It also forwards the values for further processing.
 */
template <typename OutputStreamT, typename InSeparatorT = detail::empty_output>
auto write(OutputStreamT& stream, InSeparatorT in_sep = InSeparatorT{})
  -> write_t<std::reference_wrapper<OutputStreamT>,
             InSeparatorT,
             InSeparatorT>
{
  auto arg_sep = in_sep;
  return { std::ref(stream), std::move(in_sep), std::move(arg_sep) };
}

template <typename OutputStreamT, typename InSeparatorT, typename ArgSeparatorT>
auto write(OutputStreamT& stream, InSeparatorT in_sep, ArgSeparatorT arg_sep)
  -> write_t<std::reference_wrapper<OutputStreamT>,
             InSeparatorT,
             ArgSeparatorT>
{
  return { std::ref(stream), std::move(in_sep), std::move(arg_sep) };
}

} // namespace xform
} // namespace atria
