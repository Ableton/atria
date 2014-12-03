// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/testing/Spies.hpp>
#include <ableton/testing/gtest.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant.hpp>
ABL_RESTORE_WARNINGS
#include <string>

namespace ableton {
namespace testing {

TEST(VariantSpy, CountsOcurrencesForEachType)
{
  auto s = VariantSpy {};

  s(int{});
  EXPECT_EQ(s.count(), 1);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 0);

  s(float{});
  EXPECT_EQ(s.count(), 2);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 1);

  s(int{});
  EXPECT_EQ(s.count(), 3);
  EXPECT_EQ(s.count<int>(), 2);
  EXPECT_EQ(s.count<float>(), 1);
}

TEST(VariantSpy, CanGeneratePartiallyAppliedVisitorForVariant)
{
  using SomeVariant = boost::variant<int, float, std::string>;

  auto s = VariantSpy {};
  auto v = s.visitor<SomeVariant>();

  v(SomeVariant {int {}});
  EXPECT_EQ(s.count(), 1);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 0);

  v(SomeVariant {float {}});
  EXPECT_EQ(s.count(), 2);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 1);
}

namespace {

using namespace testing::mocks;

struct SomeMock
{
  Spy<> doStuff;
  Spy<Default<int>> getSize;
  Spy<Return<std::string>> getName = [this] {
    return this->mName;
  };
  Spy<std::function<int(float, float)>> sumate = [](float a, float b) {
    return a + b;
  };

  explicit SomeMock(std::string name = "noone")
    : mName(name)
  {}

private:
  std::string mName;
};

} // namespace anon

TEST(Spy_Mocks_Default, DefaultMocksReturnDefaultConstructedObject)
{
  auto mock = SomeMock {};
  static_assert(std::is_same<decltype(mock.doStuff()), void>::value,
                "Mock should return void");
  static_assert(std::is_same<decltype(mock.getSize()), int>::value,
                "Mock should return int");
  EXPECT_EQ(mock.getSize(), int{});
}

TEST(Spy_Mocks_Default, DefaulMocksCanTakeArbitraryParameters)
{
  auto mock = SomeMock {};
  mock.doStuff();
  EXPECT_EQ(mock.doStuff.count(), 1);

  mock.doStuff(32, "hola", nullptr);
  EXPECT_EQ(mock.doStuff.count(), 2);

  mock.getSize(32, "hola", nullptr);
  EXPECT_EQ(mock.getSize.count(), 1);

  mock.getSize();
  EXPECT_EQ(mock.getSize.count(), 2);
}

TEST(Spy_Mocks_Return, ReturnMocksEvaluateFunction)
{
  EXPECT_EQ(SomeMock{"hello"}.getName(), "hello");
  EXPECT_EQ(SomeMock{"john"}.getName(), "john");
}

TEST(Spy_Mocks_Function, FunctionMocksEvaluateFunction)
{
  EXPECT_EQ(SomeMock{"hello"}.sumate(32, 42), 74);
}

TEST(Spy_Mocks_Function, FunctionMocksDontTakeArbitraryArguments)
{
  // Doesn't compile, this returns one argument too many.
  //
  //   EXPECT_EQ(SomeMock{"hello"}.sumate(32, 42, 12), nullptr);
}

TEST(Spy, TrivialSpyFactory)
{
  auto s = spy();
  EXPECT_EQ(s.count(), 0);

  s();
  EXPECT_EQ(s.count(), 1);

  s();
  EXPECT_EQ(s.count(), 2);
}

TEST(Spy, SpyFactoryWithFunction)
{
  auto s = spy([] (int x) { return x + 42; });
  EXPECT_EQ(s.count(), 0);

  EXPECT_EQ(s(12), 54);
  EXPECT_EQ(s.count(), 1);

  EXPECT_EQ(s(1), 43);
  EXPECT_EQ(s.count(), 2);
}

TEST(Spy, CopiedSpiesShareState)
{
  auto s1 = spy([] (int x) { return x + 42; });

  s1(12);
  EXPECT_EQ(s1.count(), 1);

  auto s2 = s1;
  EXPECT_EQ(s1.count(), 1);
  EXPECT_EQ(s2.count(), 1);

  s2(42);
  EXPECT_EQ(s1.count(), 2);
  EXPECT_EQ(s2.count(), 2);
}

namespace {

struct AnotherMock
{
  template <typename Signature>
  using Mock = std::function<Signature>;

  Mock<void()> doStuff = [] {};
  Mock<int()> getSize = [] {
    return int{};
  };
  Mock<std::string()> getName = [this] {
    return this->mName;
  };
  Mock<int(float, float)> sumate = [](float a, float b) {
    return a + b;
  };

  explicit AnotherMock(std::string name = "noone")
    : mName(name)
  {}

private:
  std::string mName;
};

} // namespace

TEST(SpyOn, DynamicallySpyOnFunction)
{
  auto orig = std::function<int()> {[] { return 42; }};
  auto s = spyOn(orig);
  EXPECT_EQ(s.count(), 0);

  EXPECT_EQ(orig(), 42);
  EXPECT_EQ(s.count(), 1);
}

TEST(SpyOn, DynamicallySpyOnFunctionTwice)
{
  auto orig = std::function<int()> {[] { return 42; }};
  auto s1 = spyOn(orig);

  orig();
  EXPECT_EQ(s1.count(), 1);

  auto s2 = spyOn(orig);
  orig();
  EXPECT_EQ(s2.count(), 1);
  EXPECT_EQ(s1.count(), 2);
}

TEST(SpyOn, ScopedReplacement)
{
  auto orig = std::function<int()> {[] { return 42; }};

  {
    auto s1 = spyOn(orig, []{ return 26; });
    EXPECT_EQ(orig(), 26);
    EXPECT_EQ(s1.count(), 1);
  }

  EXPECT_EQ(orig(), 42);
}

TEST(SpyOn, RealisitcExampleOfDynamicMockingWithReplacementMethod)
{
  auto mock = AnotherMock {};

  auto s1 = spyOn(mock.sumate);
  EXPECT_EQ(mock.sumate(2, 2), 4);
  EXPECT_EQ(s1.count(), 1);

  auto s2 = spyOn(mock.getName, [] {
      return "fixed";
    });
  EXPECT_EQ(mock.getName(), "fixed");
  EXPECT_EQ(s2.count(), 1);
}

} // namespace testing
} // namespace ableton
