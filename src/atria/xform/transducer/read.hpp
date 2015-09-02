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

namespace atria {
namespace xform {

namespace detail {

template <typename ValueT>
struct read_rf_gen
{
  template <typename ReducingFnT, typename InputStreamRefT>
  struct apply
  {
    ReducingFnT step;
    InputStreamRefT stream_ref;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> decltype(reduced(skip(step,
                               state_unwrap(std::forward<StateT>(s)),
                               std::forward<InputTs>(is)...,
                               std::declval<ValueT>())))
    {
      ValueT value{};
      auto& stream = stream_ref.get();
      if (stream) {
        stream >> value;
        if (!stream.fail())
          return not_reduced(
            call(step,
                 state_unwrap(std::forward<StateT>(s)),
                 std::forward<InputTs>(is)...,
                 std::move(value)));
      }
      return reduced(
        skip(step,
             state_unwrap(std::forward<StateT>(s)),
             std::forward<InputTs>(is)...,
             std::move(value)));
    }
  };
};

} // namespace detail

template <typename T, typename InputStreamRefT>
using read_t = transducer_impl<detail::read_rf_gen<T>, InputStreamRefT>;

/*!
 * Generator transducer that produces a sequence of values of type `T`
 * read from the given @a `stream` using the `operator >>`.  If more
 * than one type is passed, it reads multiple values producing `T0,
 * T1, ..., Tn` on each iteration.
 */
template <typename T, typename InputStreamT>
auto read(InputStreamT& stream)
  -> read_t<T, std::reference_wrapper<InputStreamT> >
{
  return { std::ref(stream) };
}

template <typename T1, typename T2, typename ...Ts, typename InputStreamT>
auto read(InputStreamT& stream)
  -> ABL_DECLTYPE_RETURN(
    comp(read<T1>(stream),
         read<T2>(stream),
         read<Ts>(stream)...))

} // namespace xform
} // namespace atria
