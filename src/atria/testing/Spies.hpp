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
class VariantSpy : public boost::static_visitor<>
{
public:
  struct AllVariants {};

  template <typename T>
  void operator()(const T&)
  {
    mCalls.insert(typeid(T));
    mCalls.insert(typeid(AllVariants));
  }

  template <typename T = AllVariants>
  std::size_t count() const
  {
    return mCalls.count(typeid(T));
  }

  template<typename VariantT>
  auto visitor()
    -> decltype(std::bind(
                  static_cast<void (*) (VariantSpy&, const VariantT&)>(
                    &boost::apply_visitor<VariantSpy, const VariantT>),
                  std::ref(*this),
                  std::placeholders::_1))
  {
    return std::bind(
      static_cast<void (*) (VariantSpy&, const VariantT&)>(
        &boost::apply_visitor<VariantSpy, const VariantT>),
      std::ref(*this),
      std::placeholders::_1);
  }

private:
  std::unordered_multiset<std::type_index> mCalls;
};

namespace mocks {

template<typename T>
struct Default
{
  template <typename... Args>
  T operator() (Args&& ...args) { return T(); }
};

template<typename T>
struct Return
{
  Return() = default;

  template<typename Fn>
  Return(const Fn& mock)
    : mMock(mock)
  {}

  template <typename... Args>
  T operator() (Args&& ...args) {
    return mMock();
  }

private:
  std::function<T()> mMock;
};

} // namespace mocks

namespace detail {

class SpyBase
{
public:
  std::size_t count() const
  {
    return *mCount;
  }

  void called()
  {
    ++ *mCount;
  }

private:
  std::shared_ptr<std::size_t> mCount = std::make_shared<std::size_t>(0);
};

} // namespace detail

//!
// Functor that counts the number of times it was called.
//
// @todo Support comparing the actual arguments.  Keep generic
// interface using boost::any
//
template<typename MockT = mocks::Default<void> >
class Spy : public detail::SpyBase
{
  MockT mMock;

public:
  Spy() = default;

  template<typename MockT2>
  Spy(MockT2 mock)
    : mMock(std::move(mock))
  {}

  template<typename MockT2>
  Spy(MockT2 mock, const SpyBase& spy)
    : SpyBase(spy)
    , mMock(std::move(mock))
  {}

  template <typename... Args>
  auto operator() (Args&& ...args)
    -> decltype(this->mMock(std::forward<Args>(args)...))
  {
    called();
    return this->mMock(std::forward<Args>(args)...);
  }
};

//!
// Returns a spy object that uses fn as mock implementation.
//
template <typename Fn>
inline Spy<Fn> spy(const Fn& fn)
{
  return Spy<Fn>(fn);
}

//!
// Returns a spy object with a no-op mock implementation.
//
inline Spy<> spy()
{
  return Spy<>();
}

namespace detail {

template <typename MockT>
class ScopedIntruder
{
  boost::optional<MockT&> mMock;
  MockT mOriginal;

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
    : mMock(mock)
    , mOriginal(mock)
  {
    *mMock = replacement;
  }

  ~ScopedIntruder()
  {
    if (mMock)
    {
      *mMock = mOriginal;
    }
  }

  template <typename ...Args>
  auto operator() (Args&& ...args)
    -> decltype((*mMock)(std::forward<Args>(args)...))
  {
    assert(mMock && "must not call intruder after having moved from it");
    return (*mMock)(std::forward<Args>(args)...);
  }

  friend void swap(ScopedIntruder& a, ScopedIntruder& b)
  {
    swap(a.mMock, b.mMock);
    swap(a.mOriginal, b.mOriginal);
  }
};

} // namespace detail

//!
// Given a functor object `mock` of a general functor with type erasure
// (e.g. std::function or boost::function) installs a spy that counts
// the calls and returns such a spy.
//
template <typename MockT>
inline Spy<detail::ScopedIntruder<MockT>> spyOn(MockT& mock)
{
  auto s = spy(mock);
  return { detail::ScopedIntruder<MockT>(mock, s), s };
}

//!
// Like @a spyOn(), but it installs the `replacement` function instead
// of keeping the original one.  The spy is uninstalled on
// destruction, and it is not copyable.
//
template <typename MockT, typename FnT>
inline Spy<detail::ScopedIntruder<MockT>>
spyOn(MockT& mock, const FnT& replacement)
{
  auto s = spy(replacement);
  return { detail::ScopedIntruder<MockT>(mock, s), s };
}

} // namespace testing
} // namespace atria
