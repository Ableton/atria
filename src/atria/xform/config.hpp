// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

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
 * `transducer<>` and stateful reducers.
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
 * case, halting reducers (e.g. take) might not work.
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
