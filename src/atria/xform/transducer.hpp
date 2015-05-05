// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducers.hpp>
#include <atria/xform/state.hpp>
#include <atria/xform/any_state.hpp>

#include <functional>

namespace atria {
namespace xform {

namespace detail {

struct type_erased_reducer
{
  template <typename CompleteT,
            typename ReduceT>
  struct tag {
    using complete_t = CompleteT;
    using reduce_t   = ReduceT;
  };

  template <typename AsStateT>
  struct from_any_state_reducer
  {
    template <typename ReducerT>
    struct apply
    {
      ReducerT reducer;

      template <typename StateT, typename ...InputTs>
      auto operator() (StateT&& s, InputTs&& ...is)
        -> decltype(reducer(std::forward<StateT>(s).template as<AsStateT>(),
                            std::forward<InputTs>(is)...))
      {
        return reducer(std::forward<StateT>(s).template as<AsStateT>(),
                       std::forward<InputTs>(is)...);
      }
    };
  };

  template <typename AsStateT>
  using from_any_state = detail::transducer_impl<
    from_any_state_reducer<estd::decay_t<AsStateT> > >;

  template <typename ReducerT,
            typename XformT>
  struct apply
  {
    ReducerT reducer;
    XformT xform;

    using xformed_t = typename XformT::result_type;
    using output_t  = typename XformT::argument_type::second_argument_type;

    template <typename StateT, typename... InputTs>
    auto operator() (StateT&& st, InputTs&& ...ins)
      -> estd::enable_if_t<
         !is_state_wrapper<StateT>::value,
           state_wrapper<
             type_erased_reducer::tag<
               estd::decay_t<StateT>,
               estd::decay_t<decltype(reducer(st, std::declval<output_t>()))> >,
             any_state,
             xformed_t
           >
        >
    {
      using complete_t = estd::decay_t<StateT>;
      using reduce_t = estd::decay_t<
        decltype(reducer(st, std::declval<output_t>()))>;
      using tag_t = type_erased_reducer::tag<complete_t, reduce_t>;

      return wrap_state<tag_t> (
        comp(xform, from_any_state<complete_t>{}) (reducer) (
          std::forward<StateT>(st),
          std::forward<InputTs>(ins)...),
        comp(xform, from_any_state<reduce_t>{}) (reducer));
    }

    template <typename StateT, typename... InputTs>
    auto operator() (StateT st, InputTs&& ...ins)
      -> estd::enable_if_t<
           is_state_wrapper<StateT>::value,
           estd::decay_t<StateT>
        >
    {
      std::get<0>(st) = std::get<1>(st) (
        std::move(std::get<0>(st)),
        std::forward<InputTs>(ins)...);
      return st;
    }
  };
};

} // namespace detail

template <typename _1, typename _2, typename _3, typename _4>
struct state_traits<
  state_wrapper<detail::type_erased_reducer::tag<_1, _2>, _3, _4>
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

//!
// Type erased transducer.
//
// This allows to store transducers in places where the full type can
// not be known at compile time.  The `InputT` template argument is
// the type of the input over which you may apply the transducer.
// For example:
//
// @code{.cpp}
// transducer<int> filter_odd = filter([] (int x) {
//     return x % 2;
// });
// @endcode
//
// Using function style sintax one might specify the type of the data
// after running through the transducer.
//
// @code{.cpp}
// transducer<std::string(int)> serialize = map([] (int x) {
//     return std::to_string(x);
// });
// @endcode
//
// Function style syntax can be used to specify the output and input
// type.  This allows to specify transducers that may be applied over
// multiple inputs.
//
// @code{.cpp}
// transducer<float(int, int)> serialize = map([] (int a, int b) {
//     return float(a) / float(b);
// });
// @endcode
//
// @note Type erased transducers have a performance cost.  Not only is
//       it slower to pass them around, they are significantly slower
//       when processing the sequence.  For such, use them when really
//       needed, and otherwise use `auto` and templates to avoid
//       erasing the types of the transducers.
//
// @note A type erased transducer actually defers applying the held
//       transducer until it first runs through a sequence, as
//       ilustrated by this example:
//
//       @code{.cpp}
//       transducer<int> filter_odd = [](auto reducer) {
//           std::cout << "Building reducer" << std::endl;
//           return [](auto st, int x) {
//               return x % 2 ? reducer(st, x) : st;
//           };
//       };
//
//       // Doesn't print anything
//       auto reducer = filter_odd(std::plus<>{});
//
//       // Now it prints
//       auto sum = reduce(reducer, 0, {1, 2, 3})
//       @endcode
//
template <typename SignatureT>
using transducer = detail::transducer_impl<
  detail::type_erased_reducer,
  detail::transducer_function_t<SignatureT> >;

} // namespace xform
} // namespace atria
