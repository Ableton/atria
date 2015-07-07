// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/meta/pack.hpp>
#include <atria/xform/any_state.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer_impl.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

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
          typename... OutputTs>
struct transducer_state
{
  template <typename WrappedT>
  struct make_state_wrapper
  {
    using xformed_t = typename XformT::result_type;
    using tag_t     = transducer_tag<
      estd::decay_t<StateT>,
      estd::decay_t<decltype(std::declval<ReducingFnT>()(
                               std::declval<StateT>(),
                               std::declval<OutputTs>()...))> >;
    using type      = state_wrapper<tag_t, WrappedT, xformed_t>;
  };

  using type = typename boost::mpl::eval_if_c<
      is_state_wrapper<StateT>::value,
      boost::mpl::identity<estd::decay_t<StateT> >,
      make_state_wrapper<any_state>
    >::type;
};

template <typename StateT,
          typename ReducingFnT,
          typename XformT,
          typename... OutputTs>
using transducer_state_t = typename transducer_state<
  StateT, ReducingFnT, XformT, OutputTs...>::type;

template <typename... OutputTs>
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
        auto next = step(std::move(s).as<AsStateT>(),
                         std::forward<InputTs>(is)...);
        s = std::move(next);
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

    template <typename StateT, typename... InputTs>
    auto operator() (StateT st, InputTs&& ...ins)
      -> transducer_state_t<StateT, ReducingFnT, XformT, OutputTs...>
    {
      using wrapped_t = transducer_state_t<
        StateT, ReducingFnT, XformT, OutputTs...>;
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
          auto next = state_wrapper_data(sst)(
            std::move(state_unwrap(sst)),
            std::forward<InputTs>(ins)...);
          state_unwrap(sst) = std::move(next);
          return std::move(sst);
        });
    }
  };
};

template <typename C, typename R, typename T>
auto state_wrapper_complete(transducer_tag<C, R>, T&& wrapper) -> C
{
  return state_complete(state_unwrap(std::forward<T>(wrapper)))
    .template as<C>();
}

template <template<typename...> class MF, typename ArgT>
struct unpack : MF<ArgT> {};

template <template<typename...> class MF, typename... ArgTs>
struct unpack<MF, meta::pack<ArgTs...> > : MF<ArgTs...> {};

template <template<typename...> class MF, typename T>
using unpack_t = typename unpack<MF, T>::type;

template <typename... ArgTs>
struct reducing_function
{
  using type = std::function<any_state(any_state, ArgTs...)>;
};

template <typename InputT, typename OutputT>
using transducer_function_t = std::function<
  unpack_t<reducing_function, InputT> (
    unpack_t<reducing_function, OutputT>)>;

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
 * A second template argument can be passed to indicate the type of
 * data after running through the transducer.  By default, it's the
 * same as the input.
 *
 * @code{.cpp}
 * transducer<int, std::string> serialize = map([] (int x) {
 *     return std::to_string(x);
 * });
 * @endcode
 *
 * Both the first or second template arguments can take a
 * `meta::pack<>` when it can take or pass more than one input type.
 *
 * @code{.cpp}
 * transducer<pack<int, int>, float> serialize = map([] (int a, int b) {
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
template <typename InputT, typename OutputT=InputT>
using transducer = transducer_impl<
  detail::unpack<detail::transducer_rf_gen, OutputT>,
  detail::transducer_function_t<InputT, OutputT> >;

} // namespace xform
} // namespace atria
