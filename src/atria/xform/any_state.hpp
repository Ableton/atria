// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <atria/estd/memory.hpp>
#include <string>

#define ABL_SAFE_ANY 0

namespace atria {
namespace xform {

//!
// Polymorphically holds any value implementing the `state_traits`.
// This type is used for the implementation of `transducer`.
//
class any_state
{
public:
  any_state() noexcept
    : content(nullptr)
    {}

  any_state(any_state&&) = default;
  any_state(const any_state& other)
    : content(other.content ? other.content->clone() : nullptr)
    {}

  template<typename ValueType>
  any_state(const ValueType& value,
            estd::enable_if_t<
              !std::is_base_of<any_state, ValueType >::value
            >* = 0)
    : content(estd::make_unique<holder<ValueType> >(value))
    {}

  template<typename ValueType>
  any_state(ValueType&& value,
            estd::enable_if_t<
              !std::is_base_of<any_state,
                               estd::decay_t<ValueType> >::value
            >* = 0)
    : content(estd::make_unique<holder<estd::decay_t<ValueType> > >(
                std::forward<ValueType>(value)))
    {}

  any_state& operator=(any_state&&) = default;

  any_state & operator=(const any_state& rhs)
  {
    auto obj = rhs;
    return *this = std::move(obj);
  }

  template <typename T>
  estd::decay_t<T>& as() & {
#if ABL_SAFE_ANY
    check<T>();
#endif
    return static_cast<holder<estd::decay_t<T> >*>(content.get())->held;
  }

  template <typename T>
  estd::decay_t<T>&& as() && {
#if ABL_SAFE_ANY
    check<T>();
#endif
    return std::move(static_cast<holder<estd::decay_t<T> >*>(content.get())->held);
  }

  template <typename T>
  const estd::decay_t<T>& as() const& {
#if ABL_SAFE_ANY
    check<T>();
#endif
    return static_cast<holder<estd::decay_t<T> > const *>(content.get())->held;
  }

  template <typename T>
  const void check() const {
    if (!has<T>()) {
      throw std::runtime_error(
        std::string("Have ") + type().name() +
        ", but expect " + typeid(estd::decay_t<T>).name());
    }
  }

  template <typename T>
  bool has() const {
    return content && content->type() == typeid(estd::decay_t<T>);
  }

  const std::type_info& type() const noexcept {
    return content ? content->type() : typeid(void);
  }

private:
  friend struct state_traits<any_state>;

  struct holder_base
  {
    virtual ~holder_base() {};
    virtual const std::type_info& type() const noexcept = 0;
    virtual std::unique_ptr<holder_base> clone() const = 0;
    virtual any_state complete() const = 0;
    virtual bool is_reduced() const = 0;
    virtual any_state unwrap() const = 0;
    virtual any_state data() const = 0;
  };

  template <typename T>
  struct holder : holder_base
  {
    T held;

    template <typename TT>
    holder(TT&& x) : held(std::forward<TT>(x)) {}

    const std::type_info& type() const noexcept override
    { return typeid(T); }

    std::unique_ptr<holder_base> clone() const override
    { return estd::make_unique<holder>(held); }

    any_state complete() const override
    { return state_complete(held); }

    bool is_reduced() const override
    { return state_is_reduced(held); }

    any_state unwrap() const override
    { return state_unwrap(held); }

    any_state data() const override
    { return state_data(held, any_state{}); }
  };

  std::unique_ptr<holder_base> content;
};

template <>
struct state_traits<any_state>
{
  template <typename T>
  static auto complete(T&& t) -> decltype(std::forward<T>(t).content->complete())
  { return std::forward<T>(t).content->complete(); }

  template <typename T>
  static auto is_reduced(T&& t) -> decltype(std::forward<T>(t).content->is_reduced())
  { return std::forward<T>(t).content->is_reduced(); }

  template <typename T>
  static auto unwrap(T&& t) -> decltype(std::forward<T>(t).content->unwrap())
  { return std::forward<T>(t).content->unwrap(); }

  template <typename T, typename D>
  static auto data(T&& t, D&& d) -> estd::decay_t<D>
  {
    auto data = t.content->data();
    return data.template has<D>()
      ? data.template as<D>()
      : std::forward<D>(d);
  }
};

} // namespace xform
} // namespace atria
