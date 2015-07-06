// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into.hpp>
#include <atria/xform/transducer/filter.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/xform/transducer/transducer.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(transducer, type_erasure)
{
  auto v = std::vector<int> { 1, 2, 3, 4 };
  auto xform = transducer<int>{};

  {
    xform = map([] (int x) { return x + 2; });
    auto res = into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 3, 4, 5, 6 }));
  }

  {
    xform = filter([] (int x) { return x % 2; });
    auto res = into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 3 }));
  }

  {
    xform = take(3);
    auto res = into(std::vector<int>{}, xform, v);
    EXPECT_EQ(res, (std::vector<int> { 1, 2, 3 }));
  }
}

TEST(transducer, variadic_type_erasure)
{
  auto xform = transducer<int(int, int)>{};
  xform = map([] (int a, int b) { return a + b; });
  auto res = into(std::vector<int>{}, xform,
                  std::vector<int> {1, 2, 3},
                  std::vector<int> {2, 3, 4});
  EXPECT_EQ(res, (std::vector<int> { 3, 5, 7 }));
}

TEST(transducer, transforming_type_erasure)
{
  auto xform = transducer<std::string(int)>{};
  xform = map([] (int a) { return std::to_string(a); });
  auto res = into(std::vector<std::string>{}, xform,
                  std::vector<int> {1, 2, 3});
  EXPECT_EQ(res, (std::vector<std::string> { "1", "2", "3" }));
}

TEST(transducer, type_erasure_and_composition)
{
  auto xform1 = transducer<int(std::string)>{};
  auto xform2 = transducer<float(int)>{};
  xform1 = map([] (std::string a) { return std::stoi(a); });
  xform2 = map([] (int a) { return float(a) / 2.0f; });

  auto xform3 = comp(xform1, xform2);
  auto res = into(std::vector<float>{}, xform3,
                    std::vector<std::string> {"1", "2", "3"});
  EXPECT_EQ(res, (std::vector<float> { 0.5f, 1.0f, 1.5f }));
}

TEST(transducer, type_erasure_and_composition_erased)
{
  auto xform1 = transducer<int(std::string)>{};
  auto xform2 = transducer<float(int)>{};
  xform1 = map([] (std::string a) { return std::stoi(a); });
  xform2 = map([] (int a) { return float(a) / 2.0f; });

  auto xform3 = transducer<float(std::string)>{};
  xform3 = comp(xform1, xform2);
  auto res = into(std::vector<float>{}, xform3,
                  std::vector<std::string> {"1", "2", "3"});
  EXPECT_EQ(res, (std::vector<float> { 0.5f, 1.0f, 1.5f }));
}

} // namespace xform
} // namespace atria
