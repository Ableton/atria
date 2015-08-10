// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/reduce.hpp>
#include <atria/xform/state_wrapper.hpp>
#include <atria/xform/transducer_impl.hpp>
#include <atria/xform/reducing/first_rf.hpp>

#include <atria/estd/functional.hpp>
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

} // namespace xform
} // namespace atria
