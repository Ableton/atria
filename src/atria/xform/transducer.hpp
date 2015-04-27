// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/transducers.hpp>

#include <boost/any.hpp>
#include <functional>

namespace atria {
namespace xform {

namespace detail {

struct map_state_reducer
{
  template <typename ReducerT,
            typename MappingT>
  struct apply
  {
    ReducerT reducer;
    MappingT mapping;

    template <typename State, typename ...Inputs>
    auto operator() (State&& s, Inputs&& ...is)
      -> decltype(reducer(mapping(std::forward<State>(s)),
                          std::forward<Inputs>(is)...))
    {
      return reducer(mapping(std::forward<State>(s)),
                     std::forward<Inputs>(is)...);
    }
  };
};

//!
// Similar to @a map, but it maps the state instead of the input.
//
template <typename MappingT>
auto map_state(MappingT&& mapping)
  -> detail::transducer_impl<detail::map_state_reducer, estd::decay_t<MappingT> >
{
  return std::forward<MappingT>(mapping);
}

struct type_erased_reducer
{
  template <typename ReducerT,
            typename XformT>
  struct apply
  {
    ReducerT reducer;
    XformT xform;

    typename XformT::result_type xformed;

    template <typename StateT, typename InputT>
    auto operator() (StateT&& st, InputT&& in)
      -> estd::decay_t<StateT>
    {
      if (!xformed) {
        auto from_any = [](boost::any st) {
          return boost::any_cast<estd::decay_t<StateT>>(std::move(st));
        };
        xformed = comp(xform, map_state(from_any))(reducer);
      }
      try {
        return boost::any_cast<estd::decay_t<StateT>>(
          xformed(std::forward<StateT>(st),
                  std::forward<InputT>(in)));
      } catch (reduce_finished_exception<boost::any>& err) {
        reduce_finished(
          boost::any_cast<estd::decay_t<StateT>>(
            std::move(err.value)));
      }
    }
  };
};

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
    std::function<boost::any(boost::any, InputT)> (
      std::function<boost::any(boost::any, InputT2)>)>
  >;

} // namespace xform
} // namespace atria
