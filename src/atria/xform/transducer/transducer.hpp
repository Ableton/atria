// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/any_state.hpp>
#include <atria/xform/state.hpp>
#include <atria/xform/transducer_impl.hpp>

#include <functional>

namespace atria {
namespace xform {

namespace detail {

template <typename CompleteT,
          typename ReduceT>
struct transducer_tag
{
  using complete_t = CompleteT;
  using reduce_t   = ReduceT;
};

template <typename StateT,
          typename ReducingFnT,
          typename XformT,
          bool IsStateWrapper = is_state_wrapper<StateT>::value>
struct transducer_state
{
  using xformed_t = typename XformT::result_type;
  using output_t  = typename XformT::argument_type::second_argument_type;
  using tag_t     = transducer_tag<
    estd::decay_t<StateT>,
    estd::decay_t<decltype(std::declval<ReducingFnT>()(
                             std::declval<StateT>(),
                             std::declval<output_t>()))>
    >;

  using type = state_wrapper<tag_t, any_state, xformed_t>;
};

template <typename StateT, typename ReducingFnT, typename XformT>
struct transducer_state<StateT, ReducingFnT, XformT, true>
{
  using type = estd::decay_t<StateT>;
};

template <typename StateT, typename ReducingFnT, typename XformT>
using transducer_state_t = typename transducer_state<
  StateT, ReducingFnT, XformT>::type;

struct transducer_rf_gen
{
  template <typename AsStateT>
  struct from_any_state_rf_gen
  {
    template <typename ReducingFnT>
    struct apply
    {
      ReducingFnT step;

      template <typename ...InputTs>
      any_state operator() (any_state s, InputTs&& ...is)
      {
        s = step(s.as<AsStateT>(), std::forward<InputTs>(is)...);
        return s;
      }
    };
  };

  template <typename AsStateT>
  using from_any_state = transducer_impl<
    from_any_state_rf_gen<estd::decay_t<AsStateT> > >;

  template <typename ReducingFnT,
            typename XformT>
  struct apply
  {
    ReducingFnT step;
    XformT xform;

    using xformed_t = typename XformT::result_type;
    using output_t  = typename XformT::argument_type::second_argument_type;

    template <typename StateT, typename... InputTs>
    auto operator() (StateT st, InputTs&& ...ins)
      -> transducer_state_t<StateT, ReducingFnT, XformT>
    {
      using wrapped_t = transducer_state_t<StateT, ReducingFnT, XformT>;
      using tag_t = typename wrapped_t::tag;
      using reduce_t = typename tag_t::reduce_t;
      using complete_t = typename tag_t::complete_t;

      return with_state<wrapped_t>(
        std::move(st),
        [&](StateT&& sst) {
          return wrap_state<tag_t> (
            comp(xform, from_any_state<complete_t>{}) (step) (
              std::move(sst),
              std::forward<InputTs>(ins)...),
            comp(xform, from_any_state<reduce_t>{}) (step));
        },
        [&](wrapped_t&& sst) {
          std::get<0>(sst) = std::get<1>(sst)(
            std::move(std::get<0>(sst)),
            std::forward<InputTs>(ins)...);
          return std::move(sst);
        });
    }
  };
};

} // namespace detail

template <typename _1, typename _2, typename _3, typename _4>
struct state_traits<
  state_wrapper<detail::transducer_tag<_1, _2>, _3, _4>
  >
  : state_traits<state_wrapper<> >
{
  template <typename T>
  static auto complete(T&& wrapper)
    -> typename estd::decay_t<T>::tag::complete_t
  {
    return state_complete(state_unwrap(std::forward<T>(wrapper)))
      .template as<typename estd::decay_t<T>::tag::complete_t>();
  }
};

namespace detail {

template <typename InputT>
struct transducer_function
{
  using type = std::function<
    std::function<any_state(any_state, InputT)> (
      std::function<any_state(any_state, InputT)>)
    >;
};

template <typename OutputT, typename... InputTs>
struct transducer_function<OutputT(InputTs...)>
{
  using type = std::function<
    std::function<any_state(any_state, InputTs...)> (
      std::function<any_state(any_state, OutputT)>)
    >;
};

template <typename T>
using transducer_function_t = typename transducer_function<T>::type;

} // namespace detail

/*!
 * Type erased transducer.
 *
 * This allows to store transducers in places where the full type can
 * not be known at compile time.  The `InputT` template argument is
 * the type of the input over which you may apply the transducer.
 * For example:
 *
 * @code{.cpp}
 * transducer<int> filter_odd = filter([] (int x) {
 *     return x % 2;
 * });
 * @endcode
 *
 * Using function style sintax one might specify the type of the data
 * after running through the transducer.
 *
 * @code{.cpp}
 * transducer<std::string(int)> serialize = map([] (int x) {
 *     return std::to_string(x);
 * });
 * @endcode
 *
 * Function style syntax can be used to specify the output and input
 * type.  This allows to specify transducers that may be applied over
 * multiple inputs.
 *
 * @code{.cpp}
 * transducer<float(int, int)> serialize = map([] (int a, int b) {
 *     return float(a) / float(b);
 * });
 * @endcode
 *
 * @note Type erased transducers have a performance cost.  Not only is
 *       it slower to pass them around, they are significantly slower
 *       when processing the sequence.  For such, use them when really
 *       needed, and otherwise use `auto` and templates to avoid
 *       erasing the types of the transducers.
 *
 * @note A type erased transducer actually defers applying the held
 *       transducer until it first runs through a sequence, as
 *       ilustrated by this example:
 *
 *       @code{.cpp}
 *       transducer<int> filter_odd = [](auto step) {
 *           std::cout << "Building step" << std::endl;
 *           return [](auto st, int x) {
 *               return x % 2 ? step(st, x) : st;
 *           };
 *       };
 *
 *       // Doesn't print anything
 *       auto step = filter_odd(std::plus<>{});
 *
 *       // Now it prints
 *       auto sum = reduce(step, 0, {1, 2, 3})
 *       @endcode
 */
template <typename SignatureT>
using transducer = transducer_impl<
  detail::transducer_rf_gen,
  detail::transducer_function_t<SignatureT> >;

} // namespace xform
} // namespace atria
