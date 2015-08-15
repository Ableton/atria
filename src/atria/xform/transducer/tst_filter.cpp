// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/reducing/last_rf.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/transducer.hpp>
#include <atria/xform/transducer/partition.hpp>
#include <atria/xform/transducer/mapcat.hpp>
#include <atria/xform/transducer/take_while.hpp>
#include <atria/xform/transducer/traced.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(filter, concept)
{
  meta::check<Transducer_spec(decltype(filter(std::less<int>{})),
                              meta::pack<int, int>)>();
}

namespace {
bool free_odd(int x) { return x % 2 == 0; }
} // anonymous

TEST(filter, invoke)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto res = transduce(
    filter(free_odd), std::plus<int>{}, 1, v);
  EXPECT_EQ(res, 9);
}

TEST(filter, composition)
{
  auto v = std::vector<int> { 1, 2, 3, 6 };
  auto times2 = [] (int x) { return x * 2; };
  auto odd = [] (int x) { return x % 2 == 0; };

  // transducers compose from left to right, this is equivalent to
  // Haskell-like expression:
  //
  //   foldl (+) $ map times2 $ filter odd $ v
  //
  auto res = transduce(
    comp(filter(odd), map(times2)), std::plus<int>{}, 1, v);
  EXPECT_EQ(res, 17);
}

TEST(filter, make_sure_inputs_cant_be_doubly_sinked)
{
  auto orig = std::vector<int> {{1, 2, 3}};
  auto pred = [] (std::vector<int> x) { return x.size() > 2; };

  auto v = orig;
  auto x = filter(pred)(last_rf)(std::vector<int>{}, std::move(v));
  EXPECT_EQ(x, orig);
}

TEST(filter, compose_with_stateful_transducer)
{
  auto v = std::vector<int> {{1, 2, 3, 4, 5, 6}};
  auto even = [] (int x) { return x % 2 == 0; };

  auto res = transduce(
    comp(filter(even), take(2)),
    std::plus<int>{},
    1, v);
  EXPECT_EQ(res, 7);
}

TEST(filter, compose_with_stateful_transducer_type_erased)
{
  auto v = std::vector<int> {{1, 2, 3, 4, 5, 6}};
  auto even = [] (int x) { return x % 2 == 0; };

  auto res = transduce(
    comp(filter(even), transducer<int>(take(2))),
    std::plus<int>{},
    1, v);
  EXPECT_EQ(res, 7);
}

TEST(filter, compose_type_erased_with_stateful_transducer)
{
  auto v = std::vector<int> {{1, 2, 3, 4, 5, 6}};
  auto even = [] (int x) { return x % 2 == 0; };

  auto res = transduce(
    comp(transducer<int>(filter(even)),
         take(2)),
    std::plus<int>{},
    1, v);
  EXPECT_EQ(res, 7);
}

TEST(filter, type_erase_and_compose_with_stateful_transducer)
{
  auto v = std::vector<int> {{1, 2, 3, 4, 5, 6}};
  auto even = [] (int x) { return x % 2 == 0; };

  auto res = transduce(
    transducer<int>{
      comp(filter(even),
           take(2))},
    std::plus<int>{},
    1, v);
  EXPECT_EQ(res, 7);
}

TEST(filter, type_erasure_triple_mortal_back_flip)
{
  auto even = [] (int x) { return x % 2 == 0; };
  auto gt3 = [] (int x) { return x > 3; };
  auto lt8 = [] (int x) { return x < 8; };
  auto plus1 = [] (int x) { return x + 1; };
  auto times2 = [] (int x) { return x * 2; };
  auto longer3 = [] (std::vector<int> x) { return x.size() > 3u; };
  auto fstlt10 = [] (std::vector<int> x) { return !x.empty() && x[0] < 10; };

  auto v = std::vector<int> {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
  auto xform = transducer<int>{comp(
      comp(take_while(lt8),
           partition(3u),
           take(10),
           mapcat(plus1),
           filter(even),
           comp(transducer<int>{map(times2)},
                filter(gt3))),
      partition(6u),
      transducer<std::vector<int>, int>{comp(
          transducer<std::vector<int> >{filter(longer3)},
          take_while(fstlt10),
          cat,
          transducer<int>{take(2)})},
      filter(gt3),
      comp(take(5),
           transducer<int>{map(times2)},
           filter(even)))};

  auto res = transduce(
    xform,
    std::plus<int>{},
    1, v);
  EXPECT_EQ(res, 25);
}

} // namespace xform
} // namespace atria
