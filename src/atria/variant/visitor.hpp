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

#include <atria/variant/variant_types.hpp>
#include <atria/meta/common_type.hpp>
#include <atria/meta/utils.hpp>
#include <atria/estd/type_traits.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/mpl/push_back.hpp>
ABL_RESTORE_WARNINGS

#include <cassert>
#include <utility>

namespace atria {
namespace variant {

namespace detail {

template <typename ...Fns>
struct visitor_impl;

template <typename Fn, typename ...Fns>
struct visitor_impl<Fn, Fns...>
  : Fn
  , visitor_impl<Fns...>
{
  using next = visitor_impl<Fns...>;
  using Fn::operator();
  using next::operator();

  template <typename Fn2, typename ...Fns2>
  visitor_impl(Fn2&& fn, Fns2&& ...fns)
    : Fn(std::forward<Fn2>(fn))
    , next(std::forward<Fns2>(fns)...)
  {}
};

template <typename Fn>
struct visitor_impl<Fn> : Fn
{
  using Fn::operator();

  template <typename Fn2>
  visitor_impl(Fn2&& fn)
    : Fn(std::forward<Fn2>(fn))
  {}
};

} // namespace detail

/*!
 * General visitor based on a set of function objects.
 */
template <typename ReturnType, typename ...Fns>
class visitor_t
{
  detail::visitor_impl<Fns...> impl_;

  template<typename T>
  auto call_impl(std::false_type /*massage_void*/, T&& x) -> ReturnType
  {
    return impl_(std::forward<T>(x));
  }

  template<typename T>
  auto call_impl(std::true_type  /*massage_void*/, T&& x) -> ReturnType
  {
    return impl_(std::forward<T>(x)), meta::from_void{};
  }

public:
  using result_type = ReturnType;

  visitor_t(Fns&& ...fns)
    : impl_(std::forward<Fns>(fns)...)
  {}

  template<typename T, typename U=ReturnType>
  auto operator() (T&& x) -> ReturnType
  {
    return call_impl(
      std::integral_constant<
        bool,
        std::is_void<decltype(impl_(std::forward<T>(x)))>::value &&
       !std::is_void<U>::value>{},
      std::forward<T>(x));
  }
};

/*!
 * Wraps a functor such that it has a fixed return value. Can be
 * use to disambiguate cases of a variant visitor.
 */
template <typename Fn, typename ReturnType=void>
struct otherwise_t
{
  using result_type = ReturnType;

  otherwise_t(Fn&& fn)
    : impl_(std::forward<Fn>(fn))
  {}

  template <typename ...Args>
  result_type operator() (Args&& ...args)
  {
    return impl_(std::forward<Args>(args)...);
  }

private:
  Fn impl_;
};

namespace detail {

template<typename ReturnT>
struct default_construct
{
  template <typename ...Args>
  ReturnT operator() (Args&& ...)
  {
    return ReturnT{};
  }
};

} // namespace detail

template <typename ReturnType = void,
          typename Fn = detail::default_construct<ReturnType>>
otherwise_t<Fn, ReturnType>
otherwise(Fn&& fn = Fn())
{
  return { std::forward<Fn>(fn) };
}

/*!
 * Wraps a functor such that it has a fixed argument list.  Can be
 * use to disambiguate cases of a variant visitor.
 */
template <typename Fn, typename ...Args>
struct when_t
{
  using result_type = estd::result_of_t<Fn(Args...)>;

  when_t(Fn&& fn)
    : impl_(std::forward<Fn>(fn))
  {}

  result_type operator() (Args&& ...args)
  {
    return impl_(std::forward<Args>(args)...);
  }

private:
  Fn impl_;
};

/*!
 * Factory for when functors.  Returns a wrapper for functor F with
 * signature fixed to `Args`.  Copy arguments are converted to
 * `const&`, which eases use with `std::bind` and `std::mem_fn`.
 */
template <typename ...Args, typename Fn>
when_t<Fn,
       typename boost::mpl::if_<std::is_reference<Args>,
                                Args, const Args&>::type...>
when(Fn&& fn)
{
  return { std::forward<Fn>(fn) };
}

namespace detail {

template <typename AccT, typename FnT, typename T,
          typename Enable = void>
struct add_result_of_aux
{
  using type = AccT;
};

template <typename AccT, typename FnT, typename T>
struct add_result_of_aux<AccT, FnT, T,
                         estd::void_t<estd::result_of_t<FnT(T)> > >
  : boost::mpl::push_back<AccT, estd::result_of_t<FnT(T)> >
{};

template <typename AccT, typename FnT, typename Ts>
struct add_results_of;

template <typename AccT, typename FnT, typename T, typename... Ts>
struct add_results_of<AccT, FnT, meta::pack<T, Ts...> >
  : add_results_of<meta::eval_t<add_result_of_aux<AccT, FnT, T> >,
                   FnT,
                   meta::pack<Ts...> >
{};

template <typename AccT, typename FnT>
struct add_results_of<AccT, FnT, meta::pack<> >
{
  using type = AccT;
};

} // namespace detail

template <typename FnT, typename... VariantTs>
struct visitor_result_of
  : meta::unpack<
      meta::common_type,
      typename detail::add_results_of<meta::pack<>,
                                      FnT,
                                      meta::pack<VariantTs...> >::type >
{};

template <typename FnT, typename... VariantTs>
struct visitor_result_of<FnT, meta::pack<VariantTs...> >
  : visitor_result_of<FnT, VariantTs...>
{};

template <typename FnT, typename... VariantTs>
using visitor_result_of_t = typename visitor_result_of<FnT, VariantTs...>::type;

/*!
 * Returns a visitor object that can be used to deconstruct various
 * variant types, created by composing the functions `fns...`.  It
 * attempts to deduce the return type of the function, but this might
 * fail when generic functions are passed in.
 */
template <typename... FnTs>
auto visitor(FnTs&& ...fns)
  -> visitor_t<
    meta::common_type_t<
      estd::result_of_t<FnTs(meta::bottom)>...>,
    FnTs...>
{
  return { std::forward<FnTs>(fns)... };
}

template <typename FnT>
auto visitor(FnT&& fn) -> FnT&&
{
  return std::forward<FnT>(fn);
}

/*!
 * Like @a visitor, but it uses the `variant_types` in `VariantT` to
 * deduce what the return type of the visitor should be.  This allows
 * it to deduce it even if generic functions are passed in.
 */
template <typename VariantT, typename... FnTs>
auto visitor_for(FnTs&&... fns)
  -> visitor_t<
    visitor_result_of_t<
      detail::visitor_impl<FnTs...>,
      variant_types_t<VariantT> >,
    FnTs...>
{
  return { std::forward<FnTs>(fns)... };
}

template <typename VarianT, typename FnT>
auto visitor_for(FnT&& fn) -> FnT&&
{
  return std::forward<FnT>(fn);
}

} // namespace variant
} // namespace atria
