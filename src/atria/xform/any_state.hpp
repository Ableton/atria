// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/xform/config.hpp>
#include <atria/xform/state_traits.hpp>
#include <atria/estd/memory.hpp>
#include <atria/meta/pack.hpp>
#include <string>

#if ABL_TRACE_ANY_STATE_ALLOC
#include <iostream>
#endif

namespace atria {
namespace xform {

/*!
 * Polymorphically holds any value implementing the `state_traits`.
 * This type is used for the implementation of `transducer`.
 */
class any_state
{
public:
  any_state() noexcept
    : data_(reinterpret_cast<char*>(&null_holder_))
    , size_(0)
    {}

  ~any_state() noexcept {
    if (size_) {
      content()->~holder_base();
      delete [] data_;
    }
  }

  any_state(any_state&& other)
    : data_(other.data_)
  {
    auto size = other.size_;
    other.size_ = 0;
    size_ = size;
  }

  any_state(const any_state& other)
    : data_(new char[other.size_])
    , size_(other.size_)
  {
#if ABL_TRACE_ANY_STATE_ALLOC
    std::cout << "alloc-c" << std::endl;
#endif
    other.content()->clone(data_);
  }

  template<typename ValueType>
  any_state(ValueType&& value,
            estd::enable_if_t<
              !std::is_base_of<any_state,
                               estd::decay_t<ValueType> >::value
            >* = 0)
    : data_(new char[sizeof(holder<estd::decay_t<ValueType> >)])
    , size_(sizeof(holder<estd::decay_t<ValueType> >))
    {
      new (data_) holder<estd::decay_t<ValueType> >(
          std::forward<ValueType>(value));
#if ABL_TRACE_ANY_STATE_ALLOC
      std::cout << "alloc-n " << typeid(estd::decay_t<ValueType>).name() << std::endl;
#endif
    }

  any_state& operator=(any_state&& other)
  {
    data_ = other.data_;
    size_ = other.size_;
    other.size_ = 0;
    return *this;
  }

  any_state& operator=(const any_state& rhs)
  {
    if (&rhs != this) {
      realloc_(rhs.content()->size());
      rhs.content()->clone(data_);
    }
    return *this;
  }

  template <typename ValueType>
  auto operator=(ValueType&& rhs)
    -> estd::enable_if_t<
      !std::is_base_of<any_state, estd::decay_t<ValueType> >::value,
      any_state&>
  {
    realloc_(sizeof(holder<estd::decay_t<ValueType> >));
    new (data_) holder<estd::decay_t<ValueType> >(
      std::forward<ValueType>(rhs));
    return *this;
  }

  template <typename T>
  estd::decay_t<T>& as() &
    { return as_impl(meta::pack<estd::decay_t<T> >{}); }

  template <typename T>
  estd::decay_t<T>&& as() &&
    { return std::move(as_impl(meta::pack<estd::decay_t<T> >{})); }

  template <typename T>
  const estd::decay_t<T>& as() const& {
    return const_cast<any_state*>(this)->as_impl(
      meta::pack<estd::decay_t<T> >{});
  }

  template <typename T>
  void check() const {
    if (!has<T>()) {
      throw std::runtime_error(
        std::string("Have ") + type().name() +
        ", but expect " + typeid(estd::decay_t<T>).name());
    }
  }

  template <typename T>
  bool has() const {
    return content()->type() == typeid(estd::decay_t<T>);
  }

  const std::type_info& type() const noexcept {
    return content()->type();
  }

private:
  void realloc_(std::size_t size) {
    if (size_ > 0)
      content()->~holder_base();
    if (size_ < size) {
      if (size_ > 0)
        delete [] data_;
      data_ = new char[size];
      size_ = size;
#if ABL_TRACE_ANY_STATE_ALLOC
      std::cout << "alloc-r" << std::endl;
#endif
    }
  }

  template <typename T>
  T& as_impl(meta::pack<T>) {
#if ABL_SAFE_ANY_STATE
    check<T>();
#endif
    return reinterpret_cast<holder<T>*>(data_)->held;
  }

  any_state& as_impl(meta::pack<any_state>) {
    return *this;
  }

  friend struct state_traits<any_state>;

  struct holder_base
  {
    virtual ~holder_base();
    virtual const std::type_info& type() const noexcept = 0;
    virtual void clone(char* data) const = 0;
    virtual void move(char* data) const = 0;
    virtual any_state complete() const = 0;
    virtual bool is_reduced() const = 0;
    virtual any_state unwrap() const = 0;
    virtual any_state data() const = 0;
    virtual std::size_t size() const = 0;
  };

  template <typename T>
  struct holder : holder_base
  {
    T held;

    template <typename TT>
    holder(TT&& x) : held(std::forward<TT>(x)) {}

    const std::type_info& type() const noexcept override
    { return typeid(T); }

    void clone(char* data) const override
    { new (data) holder<T>(held); }

    void move(char* data) const override
    { new (data) holder<T>(std::move(held)); }

    any_state complete() const override
    { return state_complete(held); }

    bool is_reduced() const override
    { return state_is_reduced(held); }

    any_state unwrap() const override
    { return state_unwrap(held); }

    any_state data() const override
    { return state_data(held, [] { return any_state{}; }); }

    std::size_t size() const override
    { return sizeof(T); }
  };

  struct null_holder : holder_base
  {
    virtual ~null_holder();

    const std::type_info& type() const noexcept override
    { return typeid(void); }

    void clone(char* data) const override { new (data) null_holder; }
    void move(char* data) const override { new (data) null_holder; }
    any_state complete() const override { return {}; }
    bool is_reduced() const override { return false; }
    any_state unwrap() const override { return {}; }
    any_state data() const override { return {}; }
    std::size_t size() const override { return 0; }
  };

  holder_base* content() const { return reinterpret_cast<holder_base*>(data_); }

  char* data_;
  std::size_t size_;

  static null_holder null_holder_;
};

template <>
struct state_traits<any_state>
{
  template <typename T>
  static auto complete(T&& t)
    -> ABL_AUTO_RETURN(
      std::forward<T>(t).content()->complete())

  template <typename T>
  static auto is_reduced(T&& t)
    -> ABL_AUTO_RETURN(
      std::forward<T>(t).content()->is_reduced())

  template <typename T>
  static auto unwrap(T&& t)
    -> ABL_AUTO_RETURN(
      std::forward<T>(t).content()->unwrap())

  template <typename T, typename D>
  static auto data(T&& t, D&& d)
    -> estd::decay_t<decltype(std::forward<D>(d)())>
  {
    using data_t = estd::decay_t<decltype(std::forward<D>(d)())>;
    auto data = t.content()->data();
    return data.template has<data_t>()
      ? data.template as<data_t>()
      : std::forward<D>(d)();
  }
};


/*!
 * Given a value `st` that represents the state of a reduction, this
 * function generically dispatches to the right function `UnwrappedFn`
 * or `WrappedFn`, depending of whether the value is of type
 * `WrappedStateT` or not.
 *
 * - Iff the value the `st` is of type `StateT` or is a `any_state`
 *   containing a `WrappedStateT`, the `WrappedFn` function is called
 *   with the contained state `WrappedStateT` value as a parameter.
 *
 * - Otherwise, `UnwrappedFn` is called with the original `StateT`
 *   value an argument
 *
 * Both `WrappedFn` and `UnwrappedFn` are expected to return a
 * `WrappedStateT` value.
 *
 * This function can dispatch both statically and dynamically in a
 * transparent way.  It is thus very useful for writing stateful
 * transducers that can be type erased in a `transducer<>` object.
 *
 * @see transducer
 * @see take
 */
template <typename WrappedStateT,
          typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&&, WrappedFn&& fn)
  -> estd::enable_if_t<
    std::is_same<
      estd::decay_t<StateT>,
      WrappedStateT
    >::value,
    decltype(std::forward<WrappedFn>(fn)(std::forward<StateT>(st)))
  >
{
  return std::forward<WrappedFn>(fn)(std::forward<StateT>(st));
};

template <typename WrappedStateT,
          typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&& fn, WrappedFn&&)
  -> estd::enable_if_t<
    !std::is_same<estd::decay_t<StateT>, any_state>::value
    && std::is_same<
      estd::decay_t<StateT>,
      estd::decay_t<decltype(state_complete(st))>
    >::value,
    WrappedStateT
  >
{
  return std::forward<UnwrappedFn>(fn)(std::forward<StateT>(st));
};

template <typename WrappedStateT,
          typename StateT,
          typename UnwrappedFn,
          typename WrappedFn>
auto with_state(StateT&& st, UnwrappedFn&& fn1, WrappedFn&& fn2)
  -> estd::enable_if_t<
    std::is_same<
      estd::decay_t<StateT>,
      any_state
    >::value,
    WrappedStateT
  >
{
  if (!st.template has<WrappedStateT>()) {
    return std::forward<UnwrappedFn>(fn1)(
      std::forward<StateT>(st));
  } else {
    return std::forward<WrappedFn>(fn2)(
      std::forward<StateT>(st).template as<WrappedStateT>());
  }
};

} // namespace xform
} // namespace atria
