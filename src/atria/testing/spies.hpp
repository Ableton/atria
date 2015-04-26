// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/optional.hpp>
ABL_RESTORE_WARNINGS
#include <unordered_set>
#include <typeindex>
#include <functional>
#include <memory>

namespace atria {
namespace testing {

//!
// Class for spying on functions that take a variant as a parameter.
// It will visit the variant that is passed on each call, and count
// the number of ocurrences for every type.
//
// @todo Add support for checking the actual values that were passed.
//
class variant_spy : public boost::static_visitor<>
{
public:
  struct all_variants {};

  template <typename T>
  void operator()(const T&)
  {
    calls_.insert(typeid(T));
    calls_.insert(typeid(all_variants));
  }

  template <typename T = all_variants>
  std::size_t count() const
  {
    return calls_.count(typeid(T));
  }

  template<typename VariantT>
  auto visitor()
    -> decltype(std::bind(
                  static_cast<void (*) (variant_spy&, const VariantT&)>(
                    &boost::apply_visitor<variant_spy, const VariantT>),
                  std::ref(*this),
                  std::placeholders::_1))
  {
    return std::bind(
      static_cast<void (*) (variant_spy&, const VariantT&)>(
        &boost::apply_visitor<variant_spy, const VariantT>),
      std::ref(*this),
      std::placeholders::_1);
  }

private:
  std::unordered_multiset<std::type_index> calls_;
};

namespace mocks {

template<typename T>
struct defaulting
{
  template <typename... Args>
  T operator() (Args&&...) { return T(); }
};

template<typename T>
struct returning
{
  returning() = default;

  template<typename Fn>
  returning(const Fn& mock)
    : mock_(mock)
  {}

  template <typename... Args>
  T operator() (Args&& ...) {
    return mock_();
  }

private:
  std::function<T()> mock_;
};

} // namespace mocks

namespace detail {

class spy_base
{
public:
  std::size_t count() const
  {
    return *count_;
  }

  void called()
  {
    ++ *count_;
  }

private:
  std::shared_ptr<std::size_t> count_ = std::make_shared<std::size_t>(0);
};

} // namespace detail

//!
// Functor that counts the number of times it was called.
//
// @todo Support comparing the actual arguments.  Keep generic
// interface using boost::any
//
template<typename MockT = mocks::defaulting<void> >
class spy_fn : public detail::spy_base
{
  MockT mock_;

public:
  spy_fn() = default;

  template<typename MockT2>
  spy_fn(MockT2 mock)
    : mock_(std::move(mock))
  {}

  template<typename MockT2>
  spy_fn(MockT2 mock, const spy_base& spy)
    : spy_base(spy)
    , mock_(std::move(mock))
  {}

  template <typename... Args>
  auto operator() (Args&& ...args)
    -> decltype(this->mock_(std::forward<Args>(args)...))
  {
    called();
    return this->mock_(std::forward<Args>(args)...);
  }
};

//!
// Returns a spy object that uses fn as mock implementation.
//
template <typename Fn>
inline spy_fn<Fn> spy(const Fn& fn)
{
  return spy_fn<Fn>(fn);
}

//!
// Returns a spy object with a no-op mock implementation.
//
inline spy_fn<> spy()
{
  return spy_fn<>();
}

namespace detail {

template <typename MockT>
class ScopedIntruder
{
  boost::optional<MockT&> mock_;
  MockT original_;

public:
  ScopedIntruder& operator=(const ScopedIntruder&) = delete;
  ScopedIntruder(const ScopedIntruder&) = delete;

  ScopedIntruder(ScopedIntruder&& other)
  {
    swap(*this, other);
  }

  ScopedIntruder& operator=(ScopedIntruder&& other)
  {
    if (this != &other)
    {
      swap(*this, other);
    }
  }

  ScopedIntruder(MockT& mock, MockT replacement)
    : mock_(mock)
    , original_(mock)
  {
    *mock_ = replacement;
  }

  ~ScopedIntruder()
  {
    if (mock_)
    {
      *mock_ = original_;
    }
  }

  template <typename ...Args>
  auto operator() (Args&& ...args)
    -> decltype((*mock_)(std::forward<Args>(args)...))
  {
    assert(mock_ && "must not call intruder after having moved from it");
    return (*mock_)(std::forward<Args>(args)...);
  }

  friend void swap(ScopedIntruder& a, ScopedIntruder& b)
  {
    swap(a.mock_, b.mock_);
    swap(a.original_, b.original_);
  }
};

} // namespace detail

//!
// Given a functor object `mock` of a general functor with type erasure
// (e.g. std::function or boost::function) installs a spy that counts
// the calls and returns such a spy.
//
template <typename MockT>
inline spy_fn<detail::ScopedIntruder<MockT>> spy_on(MockT& mock)
{
  auto s = spy(mock);
  return { detail::ScopedIntruder<MockT>(mock, s), s };
}

//!
// Like @a spy_on(), but it installs the `replacement` function instead
// of keeping the original one.  The spy is uninstalled on
// destruction, and it is not copyable.
//
template <typename MockT, typename FnT>
inline spy_fn<detail::ScopedIntruder<MockT>>
spy_on(MockT& mock, const FnT& replacement)
{
  auto s = spy(replacement);
  return { detail::ScopedIntruder<MockT>(mock, s), s };
}

} // namespace testing
} // namespace atria
