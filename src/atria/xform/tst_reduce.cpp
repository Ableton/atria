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

#include <atria/xform/concepts.hpp>
#include <atria/xform/reduce.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/reducing/last_rf.hpp>

#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(reduce, concept)
{
  meta::check<Reducing_function_spec(estd::plus<>, int, int)>();
  meta::check<Reducing_function_spec(first_rf_t, char*, int)>();
}

TEST(reduce, protect_against_moved_self_assignment)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(reduce(first_rf, v, v), v);
}

namespace {

struct non_default
{
  non_default() = delete;
  explicit non_default(int) {}
  non_default(const non_default&) = default;
  non_default(non_default&&) = default;
  non_default& operator=(const non_default&) = default;
  non_default& operator=(non_default&&) = default;
};

struct foo_rf_gen
{
  struct tag {};

  template <typename ReducingFnT>
  struct apply
  {
    ReducingFnT step;

    template <typename StateT, typename ...InputTs>
    auto operator() (StateT&& s, InputTs&& ...is)
      -> ABL_DECLTYPE_RETURN(
        wrap_state<tag>(step(state_unwrap(std::forward<StateT>(s)),
                             std::forward<InputTs>(is)...),
                        non_default{42}))
  };
};

using foo_t = transducer_impl<foo_rf_gen>;

} // anonymous

TEST(reduce, does_not_construct_state_wrapper_from_state)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto r = reduce(foo_t{}(first_rf), 13, v);
  EXPECT_EQ(r, 13);
}

TEST(reduce, copies_values_out_of_lvalue_container)
{
  using elem = testing::copy_spy<>;

  auto x = elem{};
  auto v = std::vector<elem> { x, x, x, x };
  auto copies = x.copied.count();
  reduce(last_rf, x, v);
  EXPECT_EQ(x.copied.count(), copies + 4);
}

TEST(reduce, moves_values_out_of_rvalue_container)
{
  using elem = testing::copy_spy<>;

  auto x = elem{};
  auto v = std::vector<elem> { x, x, x, x };
  auto copies = x.copied.count();
  reduce(last_rf, std::move(x), std::move(v));
  EXPECT_EQ(x.copied.count(), copies);
}

TEST(reduce, moves_values_out_of_rvalue_container_variadic)
{
  using elem = testing::copy_spy<>;

  auto x = elem{};
  auto v1 = std::vector<elem> { x, x, x, x };
  auto v2 = v1;
  auto init = std::make_tuple(x, x);
  auto copies = x.copied.count();
  reduce(last_rf, std::move(init), std::move(v1), std::move(v2));
  EXPECT_EQ(x.copied.count(), copies);
}

} // namespace xform
} // namespace atria
