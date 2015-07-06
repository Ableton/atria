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
