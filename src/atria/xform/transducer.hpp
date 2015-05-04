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
  template <typename StateT>
  struct tag {
    using type = StateT;
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

    template <typename StateT, typename InputT>
    auto operator() (StateT&& st, InputT&& in)
      -> estd::enable_if_t<
           !is_state_wrapper<StateT>::value,
           state_wrapper<
             type_erased_reducer::tag<estd::decay_t<StateT> >,
             any_state,
             typename XformT::result_type
           >
        >
    {
      using tag_t  = type_erased_reducer::tag<estd::decay_t<StateT> >;
      auto xformed = comp(xform, from_any_state<StateT>{}) (reducer);
      auto result  = xformed(std::forward<StateT>(st),
                             std::forward<InputT>(in));
      return wrap_state<tag_t> (
        std::move(result),
        std::move(xformed));
    }

    template <typename StateT, typename InputT>
    auto operator() (StateT st, InputT&& in)
      -> estd::enable_if_t<
           is_state_wrapper<StateT>::value,
           estd::decay_t<StateT>
        >
    {
      std::get<0>(st) = std::get<1>(st) (
        std::move(std::get<0>(st)),
        std::forward<InputT>(in));
      return st;
    }
  };
};

} // namespace detail

template <typename StateT, typename _1, typename _2>
struct state_traits<
    state_wrapper<detail::type_erased_reducer::tag<StateT>, _1, _2>
  >
  : state_traits<state_wrapper<> >
{
  template <typename T>
  static auto complete(T&& wrapper)
    -> typename estd::decay_t<T>::tag::type
  {
    return state_complete(state_unwrap(std::forward<T>(wrapper)))
      .template as<typename estd::decay_t<T>::tag::type>();
  }
};

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
// A second type `InputT2` can be passed to specify the type of the
// data after running through the transducer.
//
// @code{.cpp}
// transducer<int, std::string> serialize = map([] (int x) {
//     return std::to_string(x);
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
template <typename InputT, typename InputT2=InputT>
using transducer = detail::transducer_impl<
  detail::type_erased_reducer,
  std::function<
    std::function<any_state(any_state, InputT)> (
      std::function<any_state(any_state, InputT2)>)>
  >;

} // namespace xform
} // namespace atria
