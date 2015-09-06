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
#include <atria/xform/transducer_impl.hpp>
#include <atria/prelude/comp.hpp>
#include <functional>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/iterator_range.hpp>
ABL_RESTORE_WARNINGS
#include <array>
#include <vector>

namespace atria {
namespace xform {

namespace detail {

struct readbuf_rf_gen
{
  template <typename ReducingFnT, typename InputStreamRefT, typename BufferT>
  struct apply
  {
    ReducingFnT step;
    InputStreamRefT stream_ref;
    BufferT buffer;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(reduced(step(state_unwrap(std::forward<StateT>(s)),
                               std::forward<InputTs>(is)...,
                               boost::make_iterator_range(std::declval<char*>(),
                                                          std::declval<char*>()))))
    {
      auto& stream = stream_ref.get();
      auto data = &buffer[0];
      stream.read(data, static_cast<std::streamsize>(buffer.size()));
      return reduced_if(
        step(state_unwrap(std::forward<StateT>(s)),
             std::forward<InputTs>(is)...,
             boost::make_iterator_range(
               data,
               data + stream.gcount())),
        !stream);
    }
  };
};

} // namespace detail

template <typename InputStreamRefT, typename BufferT>
using readbuf_t = transducer_impl<detail::readbuf_rf_gen,
                                  InputStreamRefT,
                                  BufferT>;

/*!
 * Generator transducer that reads buffers of size `N` from @a
 * `stream`, and passes them into the sequence.  It passes them into
 * the sequence as an range with `char*` iterators.
 */
template <std::size_t N, typename InputStreamT>
auto readbuf(InputStreamT& stream)
  -> readbuf_t<std::reference_wrapper<InputStreamT>, std::array<char, N> >
{
  return { std::ref(stream), std::array<char, N>{} };
}

/*!
 * Like `readbuf(stream)` but with runtime specified size.
 */
template <typename InputStreamT>
auto readbuf(InputStreamT& stream, std::size_t n)
  -> readbuf_t<std::reference_wrapper<InputStreamT>, std::vector<char> >
{
  return { std::ref(stream), std::vector<char>(n) };
}

} // namespace xform
} // namespace atria
