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

/*!
 * When truish, `into` uses a stateful implementation that relies on
 * the existence of an output iterator for the collection.  Otherwise,
 * a mostly stateless implementation that uses `emplace_back` is used.
 */
#ifndef ABL_STATEFUL_INTO
#define ABL_STATEFUL_INTO 1
#endif

/*!
 * When tryish, dynamic type checks are performed when accessing the
 * underlying state of `any_state` instances.  Useful when debugging
 * `transducer<>` and stateful reducing functions.
 */
#ifndef ABL_SAFE_ANY_STATE
#define ABL_SAFE_ANY_STATE 0
#endif

/*!
 * When tryish, messages are printed on the terminal when allocations
 * are produced inside an `any_state` object.  Useful when debugging
 * potential `transducer<>` related performance degradations.
 */
#ifndef ABL_TRACE_ANY_STATE_ALLOC
#define ABL_TRACE_ANY_STATE_ALLOC 0
#endif

/*!
 * When defined to 1, a tail-recursive definition will be used for the
 * non-variadic reduce.
 */
#ifndef ABL_REDUCE_TAIL_RECURSIVE
#define ABL_REDUCE_TAIL_RECURSIVE 0
#endif

/*!
 * When defined to 1, std::accumulate will be used as an
 * implementation for reduce() over one single collection.  In that
 * case, halting reducing functions (e.g. take) might not work.
 */
#ifndef ABL_REDUCE_WITH_ACCUMULATE
#define ABL_REDUCE_WITH_ACCUMULATE 0
#endif

/*!
 * When defined to 1, reduce will used a variadic implementation also
 * when one single input is provided.
 */
#ifndef ABL_REDUCE_ALWAYS_VARIADIC
#define ABL_REDUCE_ALWAYS_VARIADIC 0
#endif

/*!
 * There is a pattern in using `with_state` with deduced return types
 * that is making GCC 5 go nuts.  This can be used to disable that
 * code so at least we can try some other things with GCC.
 */
#ifndef ABL_MAKE_GCC_CRASH
#define ABL_MAKE_GCC_CRASH !defined(__GNUC__) || defined(__clang__ ) || defined(__llvm__)
#endif
