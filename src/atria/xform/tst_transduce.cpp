// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/any_state.hpp>
#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/take.hpp>

#include <atria/estd/functional.hpp>
#include <atria/testing/gtest.hpp>
#include <vector>

namespace atria {
namespace xform {

TEST(transduce, identity)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  EXPECT_EQ(transduce(identity, std::plus<int>{}, 1, v), 13);
}

TEST(transduce, variadic)
{
  auto v1 = std::vector<int> { 1, 2, 3, 6 };
  auto v2 = std::vector<int> { 1, 2, 1, 2 };

  EXPECT_EQ(transduce(map(std::multiplies<int>{}),
                      std::plus<int>{},
                      1,
                      v1, v2),
            21);
}

TEST(transduce, early_termination_does_not_leak)
{
  auto v1 = { 1, 2, 3, 4 };

  EXPECT_EQ(transduce(take(2),
                      std::plus<int>{},
                      0,
                      v1),
            3);
}

TEST(into, mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };
  auto res = std::vector<int> { };

  auto& res2 = into(res, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  EXPECT_EQ(&res, &res2);
}

TEST(into, non_mutation)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> {}, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
}

TEST(into, appends)
{
  auto v = std::vector<int> { 1, 2, 3 };

  auto res = into(std::vector<int> { 0 }, identity, v);
  EXPECT_EQ(res, (std::vector<int> { 0, 1, 2, 3 }));
}

TEST(into, transduction)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };

  auto res = into(
    std::vector<std::string> {},
    comp(filter([] (int x) { return x % 2 == 0; }),
         map([] (int x) { return std::to_string(x); })),
    v);
  EXPECT_EQ(res, (std::vector<std::string> { "2", "4" }));
}

TEST(into, zipping)
{
  auto v1 = std::vector<int> { 1, 2, 3, 4 };
  auto v2 = std::vector<std::string> { "a", "b" };

  using tup = std::tuple<int, std::string>;

  auto res = into(
    std::vector<tup> {},
    identity,
    v1, v2);
  EXPECT_EQ(res, (std::vector<tup> { tup(1, "a"), tup(2, "b") }));
}

TEST(state, state_concept)
{
  meta::check<State_spec(int)>();
  meta::check<State_spec(state_wrapper<void, int, int>)>();
  meta::check<State_spec(any_state)>();
  meta::check<Reducer_spec(estd::plus<>, int, int)>();
  meta::check<Transducer_spec(decltype(map(tuplify)))>();
}

} // namespace xform
} // namespace atria
