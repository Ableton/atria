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

#include <atria/xform/reductor.hpp>
#include <atria/xform/meta.hpp>
#include <atria/xform/detail/tuple_utils.hpp>
#include <atria/meta/value_type.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/mpl/eval_if.hpp>
ABL_RESTORE_WARNINGS
#include <vector>
#include <iostream>

namespace atria {
namespace xform {

namespace detail {

template <typename ValueT, typename XformT, typename... IteratorTs>
struct sequence_data
{
  using value_t = ValueT;
  using cache_t = std::vector<value_t>;
  using state_t = sequence_data*;

  struct step_t
  {
    template <typename... Ts>
    state_t operator() (state_t s, Ts&& ...xs)
    {
      s->impl_.cache.emplace_back(std::forward<Ts>(xs)...);
      return s;
    }
  };

  using reductor_t = reductor_fn<
    estd::decay_t<estd::result_of_t<XformT(step_t)> >,
    state_t,
    meta::value_t<IteratorTs>... >;

  template <typename... RangeTs>
  sequence_data(XformT xform, const RangeTs& ...ranges)
    : impl_ {
      std::size_t {},
      cache_t {},
      reductor_t {
        std::move(xform)(step_t{}),
        this,
        *std::begin(ranges)...},
      std::make_tuple(++std::begin(ranges)...),
      std::make_tuple(std::end(ranges)...)
    }
  {
    pull();
  }

  sequence_data(sequence_data&& other)
    : impl_(std::move(other.impl_))
    { impl_.reductor.current(this); }

  sequence_data(const sequence_data& other)
    : impl_(other.impl_)
    { impl_.reductor.current(this); }

  sequence_data& operator=(sequence_data&& other)
  {
    impl_ = std::move(other.impl);
    impl_.reductor.current(this);
  }

  sequence_data& operator=(const sequence_data& other)
  {
    using std::swap;
    sequence_data copied{ other };
    swap(*this, copied);
    return *this;
  }

  bool empty() const
  {
    return impl_.pos == impl_.cache.size() && (
      !impl_.reductor ||
      !detail::tuple_all_neq(impl_.firsts, impl_.lasts));
  }

  const value_t& front() const
  {
    return impl_.cache[impl_.pos];
  }

  void pop()
  {
    ++ impl_.pos;
    pull();
  }

  bool operator==(const sequence_data& other) const
  {
    return impl_.firsts == other.impl_.firsts
      && impl_.pos == other.impl_.pos;
  }

  bool operator!=(const sequence_data& other) const
    { return !(*this == other); }

private:
  void pull()
  { pull(estd::make_index_sequence<sizeof...(IteratorTs)>{}); }

  template <std::size_t... Indexes>
  void pull(estd::index_sequence<Indexes...>)
  {
    if (impl_.pos == impl_.cache.size())
    {
      impl_.cache.clear();
      impl_.pos = 0;
      while (impl_.cache.empty() &&
             impl_.reductor &&
             detail::tuple_all_neq(impl_.firsts, impl_.lasts))
      {
        using std::get;
        impl_.reductor(*get<Indexes>(impl_.firsts)...);
        meta::noop(++get<Indexes>(impl_.firsts)...);
      }
    }
  }

  struct {
    std::size_t pos;
    cache_t cache;
    reductor_t reductor;
    std::tuple<IteratorTs...> firsts;
    std::tuple<IteratorTs...> lasts;
  } impl_;
};

} // namespace detail

/*!
 * Range adaptor that transduces the ranges in `RangeTs` with the
 * transducer `XformT`, producing values of `ValueT`.  It also works
 * with no range, as a generator.
 *
 * @note There is no shared data between the range iterators excepting
 *       the adapted ranges, for which a const reference is kept.
 *       This means that it is safe to copy the iterators around and
 *       use them from different threads.  It is also safe to use the
 *       iterators after the parent `sequence_range` is destroyed, but
 *       the adapted ranges should still be kept alive.
 *
 * @note The transducer is processed every time for each iterator.
 *       Thus, any side effects the transducer might cause will be
 *       produced whenever we run on each iterator of the range.
 *
 * @note The transducer is processed lazily.  It is ok to adapt
 *       infinite ranges or infinite generators.
 */
template <typename ValueT,
          typename XformT,
          typename... RangeTs>
struct sequence_range
{
  using data_t = detail::sequence_data<
    ValueT,
    XformT,
    decltype(std::begin(std::declval<const RangeTs&>()))...>;

  using value_type = const ValueT;

  struct iterator : boost::iterator_facade<iterator,
                                           value_type,
                                           boost::forward_traversal_tag>
  {
  private:
    friend sequence_range;
    friend class boost::iterator_core_access;

    iterator(boost::optional<data_t> data)
      : data_(data && !data->empty() ? data : boost::none)
    {}

    void increment()
    {
      data_->pop();
      if (data_->empty())
        data_ = boost::none;
    }

    bool equal(const iterator& other) const
    { return data_ == other.data_; }

    const value_type& dereference() const
    { return data_->front(); }

    boost::optional<data_t> data_;
  };

  sequence_range(XformT xform, const RangeTs& ...ranges)
    : xform_(std::move(xform))
    , ranges_(ranges...)
  {}

  using const_iterator = iterator;

  iterator begin() const { return { make_data() }; }
  iterator end() const { return { boost::none }; }

private:
  boost::optional<data_t> make_data() const
  { return make_data(estd::make_index_sequence<sizeof...(RangeTs)>{}); }

  template <std::size_t... Indexes>
  boost::optional<data_t> make_data(estd::index_sequence<Indexes...>) const
  {
    return detail::tuple_all_neq(
         std::make_tuple(std::begin(std::get<Indexes>(ranges_))...),
         std::make_tuple(std::end(std::get<Indexes>(ranges_))...))
      ? boost::make_optional(data_t { xform_, std::get<Indexes>(ranges_)... })
      : boost::none;
  }

  XformT xform_;
  std::tuple<const RangeTs&...> ranges_;
};

namespace detail {
struct deduce_value_type {};
} // namespace detail

/*!
 * Factory for `sequence_range` values producing an iterable range out
 * of a transducer, in the spirit of clojure.core/sequence$2
 *
 * @see sequence_range
 */
template <typename ValueT = detail::deduce_value_type,
          typename XformT,
          typename... RangeTs>
auto sequence(XformT&& xform, const RangeTs&... ranges)
  -> sequence_range<
    typename boost::mpl::eval_if<
        std::is_same<ValueT, detail::deduce_value_type>,
        result_of<XformT, meta::value_t<RangeTs>...>,
        meta::identity<ValueT> >::type,
    estd::decay_t<XformT>,
    estd::decay_t<RangeTs>...>
{
  return { std::forward<XformT>(xform), ranges... };
}

} // namespace xform
} // namespace atria
