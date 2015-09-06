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

#include <atria/xform/transducer_impl.hpp>
#include <functional>
#include <iterator>
#include <ios>

namespace atria {
namespace xform {

namespace detail {

struct writebuf_rf_gen
{
  template <typename ReducingFnT, typename OutputStreamRefT>
  struct apply
  {
    ReducingFnT step;
    OutputStreamRefT stream_ref;

    template <typename StateT, typename InputT, typename ...InputTs>
    auto operator() (StateT&& s, InputT&& buf, InputTs&& ...is)
      -> decltype(step(std::forward<StateT>(s),
                       std::forward<InputT>(buf),
                       std::forward<InputTs>(is)...))
    {
      using std::begin;
      using std::end;

      auto& stream = stream_ref.get();
      auto first = begin(buf);
      auto last = end(buf);
      stream.write(&*first, static_cast<std::streamsize>(
                     std::distance(first, last)));
      return step(std::forward<StateT>(s),
                  std::forward<InputT>(buf),
                  std::forward<InputTs>(is)...);
    }
  };
};

} // namespace detail

template <typename OutputStreamRefT>
using writebuf_t = transducer_impl<detail::writebuf_rf_gen, OutputStreamRefT>;

/*!
 * Generator transducer that reads buffers of size `N` from @a
 * `stream`, and passes them into the sequence.  It passes them into
 * the sequence as an range with `char*` iterators.
 */
template <typename OutputStreamT>
auto writebuf(OutputStreamT& stream)
  -> writebuf_t<std::reference_wrapper<OutputStreamT> >
{
  return { std::ref(stream) };
}

} // namespace xform
} // namespace atria
