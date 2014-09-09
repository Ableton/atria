// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#pragma once

#include <boost/signals2/signal.hpp>
#include <memory>
#include <vector>
#include <functional>

//!
// @file
//
// This module implements the signal flow in funken.  Signals can be
// connected forming two superinposed directed acyclical graphs, where
// signals flow *down* or *up*.  Signals are derived from eachother
// using transducers.
//
// The APIs for flowing up and down are asymmetric because of the way
// the graph is constructed and the semantics of information flow.
//
//   - An up-down-signal can be constructed from a up-down-signal.
//   - A down-signal can be constructed from a up-down-signa or
//     a down-signal.
//   - A signal can be appended children, but can not be appended
//     parents.
//   - Information propagates upwardes immediately, but propagates
//     upwards in two fases.
//
// In general, sucessors know a lot about their predecessors, but
// sucessors need to know very little or nothing from their sucessors.
//
// @todo We could eventually flatten signals when the sucessors knows
// the transducer of its predecessor, this could be done heuristically.
//

namespace ableton {
namespace funken {

namespace detail {

//!
// Allows comparing shared and weak pointers based on their owner.
//
constexpr struct
{
  template <typename T1, typename T2>
  bool operator() (const T1& a, const T2& b)
  {
    return
      !a.owner_before(b) &&
      !b.owner_before(a);
  }
} ownerEquals {};

//!
// Interface for children of a signal and is used to propagate
// notifications.  The notifications are propagated in two steps,
// `sendDown()` and `notify()`, not ensure that the outside world sees a
// consistent state when it receives notifications.
//
struct IDown
{
  virtual ~IDown() {};
  virtual void sendDown() = 0;
  virtual void notify() = 0;
};

//!
// Interface for signals that can send values back to their parents.
//
template <typename T>
struct IUp
{
  virtual ~IUp() {};
  virtual void sendUp(const T&) = 0;
  virtual void sendUp(T&&) = 0;
};

//!
// Base class for the various signal types.  Provides basic
// functionality for setting values and propagating them to children.
//
template <typename T>
class DownSignal
  : public std::enable_shared_from_this<DownSignal<T> >
  , public IDown
{
public:
  using value_type = T;

  DownSignal(DownSignal&&) = default;
  DownSignal(const DownSignal&) = delete;
  DownSignal& operator=(DownSignal&&) = default;
  DownSignal& operator=(const DownSignal&) = delete;

  DownSignal(T value)
    : mCurrent(std::move(value))
    , mLast(mCurrent)
    , mLastNotified(mCurrent)
  {}

  virtual void recompute() {}
  virtual void recomputeDeep() {}

  const value_type& current() const { return mCurrent; }
  const value_type& last() const { return mLast; }

  void link(std::weak_ptr<IDown> pChild)
  {
    using namespace std;
    using std::placeholders::_1;
    assert(find_if(begin(mChildren), end(mChildren),
                   bind(ownerEquals, pChild, _1))
           == end(mChildren) &&
           "Child signal must not be linked twice");
    mChildren.push_back(pChild);
  }

  template <typename U>
  void pushDown(U&& value)
  {
    if (value != mCurrent)
    {
      mCurrent = std::forward<U>(value);
      mNeedsSendDown = true;
    }
  }

  void sendDown() final
  {
    recompute();
    if (mNeedsSendDown)
    {
      mLast = mCurrent;
      mNeedsSendDown = false;
      mNeedsNotify = true;

      for (auto& wpChild : mChildren)
      {
        if (auto pChild = wpChild.lock())
        {
          pChild->sendDown();
        }
      }
    }
  }

  void notify() final
  {
    using namespace std;
    if (!mNeedsSendDown && mNeedsNotify)
    {
      mNeedsNotify = false;
      mObservers(mLastNotified, mLast);
      mLastNotified = mLast;

      auto garbage = false;
      for (std::size_t i = 0, size = mChildren.size(); i < size; ++i)
      {
        if (auto pChild = mChildren[i].lock())
        {
          pChild->notify();
        }
        else
        {
          garbage = true;
        }
      }

      if (garbage)
      {
        collect();
      }
    }
  }

  template <typename Fn>
  auto observe(Fn&& f)
    -> boost::signals2::connection
  {
    return mObservers.connect(std::forward<Fn>(f));
  }

  auto observers()
    -> boost::signals2::signal<void(const value_type&,
                                    const value_type&)>&
  {
    return mObservers;
  }

private:
  void collect()
  {
    using namespace std;
    mChildren.erase(
      remove_if(
        begin(mChildren),
        end(mChildren),
        mem_fn(&weak_ptr<IDown>::expired)),
      end(mChildren));
  }

  bool mNeedsSendDown = false;
  bool mNeedsNotify = false;
  value_type mCurrent;
  value_type mLast;
  value_type mLastNotified;
  std::vector<std::weak_ptr<IDown> > mChildren;
  boost::signals2::signal<void(const value_type&,
                               const value_type&)> mObservers;
};

//!
// Base class for signals that can send values up the signal chain.
//
template <typename T>
class UpDownSignal
  : public DownSignal<T>
  , public IUp<T>
{
  using DownSignal<T>::DownSignal;
};

} // namespace detail

} // namespace funken
} // namespace ableton
