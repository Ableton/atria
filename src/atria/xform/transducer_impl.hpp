// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.
/*!
 * @file
 */

#pragma once

#include <atria/estd/type_traits.hpp>
#include <atria/estd/utility.hpp>
#include <tuple>

namespace atria {
namespace xform {

/*!
 * Utility to write simple transducers easily.  Most transducers have
 * the following structure:
 *
 * @code{.hs}
 *  xducer params... =     -- 1. this returns a transducer
 *    \ step ->         -- 2. this is a transducer
 *       \ state, input -> -- 3. this is transformed version of 'step'
 *           f(params..., step, state, input)
 * @endcode
 *
 * Writing functions that return functions without erasing their type
 * is very cumbersome in C++11 (this is not true with generic lambdas
 * and decltype(auto) in the next standard).  The `transducer_impl`
 * type implements the first two calls. The `ReducingFnGenT` parameter
 * should have a nested template `apply` that implements the last
 * call.  It will be constructed `step, params...` and it should be
 * callable with `state, input`.
 *
 * @see map
 * @see filter
 */
template<typename ReducingFnGenT,
         typename ...ParamTs>
struct transducer_impl : std::tuple<ParamTs...>
{
  using base_t = std::tuple<ParamTs...>;

  // Constructors need to be semi-manually defined.  Otherwise
  // confusion arises because of the way Clang's std::tuple uses
  // enable_if to dispatch to the right move constructors.
  //
  //    using base_t::base_t;

  transducer_impl() = default;
  transducer_impl(const transducer_impl&) = default;
  transducer_impl(transducer_impl&&) = default;
  transducer_impl& operator=(const transducer_impl&) = default;
  transducer_impl& operator=(transducer_impl&&) = default;

  template <typename ...Ts>
  transducer_impl(Ts ...ts)
    : base_t(std::move(ts)...)
  {}

  template<typename ReducingFnT>
  constexpr auto operator() (ReducingFnT&& step) const
    -> typename ReducingFnGenT::template apply<
      estd::decay_t<ReducingFnT>,
      estd::decay_t<ParamTs>...
    >
  {
    using indexes_t = estd::make_index_sequence<sizeof...(ParamTs)>;
    return this->make(std::forward<ReducingFnT>(step), indexes_t());
  }

  template<typename ReducingFnT, std::size_t...indexes_t>
  constexpr auto make(ReducingFnT&& step, estd::index_sequence<indexes_t...>) const
    -> typename ReducingFnGenT::template apply<
      estd::decay_t<ReducingFnT>,
      estd::decay_t<ParamTs>...
    >
  {
    return { std::forward<ReducingFnT>(step),
             std::get<indexes_t>(*this)... };
  }
};

} // namespace xform
} // namespace atria
