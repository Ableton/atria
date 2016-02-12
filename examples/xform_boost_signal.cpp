//
// Copyright (C) 2014, 2015, 2016 Ableton AG, Berlin. All rights reserved.
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

#include <atria/xform/reductor.hpp>
#include <atria/xform/meta.hpp>
#include <atria/xform/run.hpp>
#include <atria/xform/transducer/read.hpp>
#include <atria/xform/transducer/write.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/enumerate.hpp>
#include <atria/xform/transducer/repeat.hpp>
#include <atria/xform/transducer/each.hpp>
#include <atria/meta/pack.hpp>
#include <atria/meta/eval.hpp>
#include <atria/meta/utils.hpp>
#include <atria/prelude/identity.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/signals2/signal.hpp>
ABL_RESTORE_WARNINGS

#include <iostream>

#if ABL_MAKE_GCC_CRASH
#if ABL_CXX14
#define BUILD_EXAMPLE_ 1
#endif
#endif

#ifndef BUILD_EXAMPLE_
#define BUILD_EXAMPLE_ 0
#endif

#if BUILD_EXAMPLE_

using namespace atria;

template <typename Signal,
          typename Signature=typename estd::decay_t<Signal>::signature_type>
struct signal_args
{};
template <typename Sig, typename R, typename... Args>
struct signal_args<Sig, R(Args...)>
{
  using type = meta::pack<Args...>;
};
ABL_METAFUNCTION_T(signal_args);

template <typename OutputT>
struct signal_from
{
  using type = boost::signals2::signal<void(OutputT)>;
};
template <typename... OutputTs>
struct signal_from<meta::pack<OutputTs...> >
{
  using type = boost::signals2::signal<void(OutputTs...)>;
};
ABL_METAFUNCTION_T(signal_from);

template <typename XformT, typename SignalT>
struct xform_signal
  : signal_from_t<xform::result_of_t<XformT, signal_args_t<SignalT> > >
{
public:
  struct step_t
  {
    template <typename... InputTs>
    xform_signal* operator() (xform_signal* s, InputTs&& ...ins)
    {
      (*s)(std::forward<InputTs>(ins)...);
      return s;
    }
  };

  using base_t = signal_from_t<xform::result_of_t<XformT,
                                                  signal_args_t<SignalT> > >;
  using state_t = xform_signal*;
  using reductor_t = xform::empty_reductor_fn<
    estd::decay_t<estd::result_of_t<XformT(step_t)> >,
    state_t,
    signal_args_t<SignalT> >;

  xform_signal(const xform_signal&) = delete;
  xform_signal& operator=(const xform_signal&) = delete;

  xform_signal(XformT xform, SignalT& signal)
    : base_t {}
    , reductor_ { std::move(xform)(step_t{}), this }
    , connection_ { signal.connect(reductor_) }
  {}

  xform_signal(xform_signal&& other)
    : base_t(std::move(other))
    , reductor_(std::move(other.reductor_))
    , connection_(std::move(other.connection_))
  {
    reductor_.current(this);
  }

  xform_signal& operator=(xform_signal&& other)
  {
    reductor_ = std::move(other.reductor_);
    connection_ = std::move(other.connection_);
    reductor_.current(this);
  }

private:
  reductor_t reductor_;
  boost::signals2::scoped_connection connection_;
};

template <typename XformT, typename SignalT>
auto make_signal(XformT&& xform, SignalT& sig)
{
  return xform_signal<estd::decay_t<XformT>, SignalT>(
    std::forward<XformT>(xform), sig);
};

int main()
{
  auto sig1 = boost::signals2::signal<void(int)> {};
  auto sig2 = make_signal(
    comp(xform::filter([](auto x) { return x > 0; }),
         xform::map([] (auto x) { return std::to_string(x); })),
    sig1);

  sig2.connect([] (auto x) {
      std::cout << "x: " << x << std::endl;
    });

  xform::run(
    comp(
      xform::read<int>(std::cin),
      xform::each(std::ref(sig1))));
}

#else

int main()
{
}

#endif // ABL_MAKE_GCC_CRASH && ABL_CXX14
