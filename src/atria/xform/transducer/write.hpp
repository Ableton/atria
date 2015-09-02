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

#include <atria/xform/maybe_reduced.hpp>
#include <atria/xform/skip.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/prelude/comp.hpp>
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
            typename TerminatorT,
            typename SeparatorT>
  struct apply
  {
    ReducingFnT step;
    OutputStreamRefT stream_ref;
    TerminatorT terminator;
    SeparatorT separator;

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
             << separator;
      impl(stream, std::forward<InputTs>(ins)...);
    }

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s),
                       std::forward<InputTs>(is)...))
    {
      auto& stream = stream_ref.get();
      impl(stream, is...);
      stream << terminator;
      return step(std::forward<StateT>(s), std::forward<InputTs>(is)...);
    }
  };
};

} // namespace detail

template <typename OutputStreamRefT, typename TerminatorT, typename SeparatorT>
using write_t = transducer_impl<detail::write_rf_gen,
                                OutputStreamRefT,
                                TerminatorT,
                                SeparatorT>;

/*!
 * Transducer that writes the into a given @a `stream` using the
 * `operator <<`.  It also forwards the values for further processing.
 */
template <typename OutputStreamT, typename TerminatorT = detail::empty_output>
auto write(OutputStreamT& stream, TerminatorT term = TerminatorT{})
  -> write_t<std::reference_wrapper<OutputStreamT>,
             TerminatorT,
             TerminatorT>
{
  auto sep = term;
  return { std::ref(stream), std::move(term), std::move(sep) };
}

template <typename OutputStreamT, typename TerminatorT, typename SeparatorT>
auto write(OutputStreamT& stream, TerminatorT term, SeparatorT sep)
  -> write_t<std::reference_wrapper<OutputStreamT>,
             TerminatorT,
             SeparatorT>
{
  return { std::ref(stream), std::move(term), std::move(sep) };
}

} // namespace xform
} // namespace atria
