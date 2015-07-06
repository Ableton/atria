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
