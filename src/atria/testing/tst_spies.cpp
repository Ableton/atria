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

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant.hpp>
ABL_RESTORE_WARNINGS
#include <string>

namespace atria {
namespace testing {

TEST(variant_spy, CountsOcurrencesForEachType)
{
  auto s = variant_spy {};

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

TEST(variant_spy, CanGeneratePartiallyAppliedVisitorForVariant)
{
  using some_variant = boost::variant<int, float, std::string>;

  auto s = variant_spy {};
  auto v = s.visitor<some_variant>();

  v(some_variant {int {}});
  EXPECT_EQ(s.count(), 1);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 0);

  v(some_variant {float {}});
  EXPECT_EQ(s.count(), 2);
  EXPECT_EQ(s.count<int>(), 1);
  EXPECT_EQ(s.count<float>(), 1);
}

namespace {

using namespace testing::mocks;

struct some_mock
{
  spy_fn<> do_stuff;
  spy_fn<defaulting<int>> get_size;
  spy_fn<returning<std::string>> get_name = [this] {
    return this->name_;
  };
  spy_fn<std::function<int(float, float)>> sumate = [](float a, float b) {
    return a + b;
  };

  explicit some_mock(std::string name = "noone")
    : name_(name)
  {}

private:
  std::string name_;
};

} // namespace anon

TEST(spy_fn_mocks_default, default_mocks_return_default_constructed_object)
{
  auto mock = some_mock {};
  static_assert(std::is_same<decltype(mock.do_stuff()), void>::value,
                "Mock should return void");
  static_assert(std::is_same<decltype(mock.get_size()), int>::value,
                "Mock should return int");
  EXPECT_EQ(mock.get_size(), int{});
}

TEST(spy_fn_mocks_default, defaul_mocks_can_take_arbitrary_parameters)
{
  auto mock = some_mock {};
  mock.do_stuff();
  EXPECT_EQ(mock.do_stuff.count(), 1);

  mock.do_stuff(32, "hola", nullptr);
  EXPECT_EQ(mock.do_stuff.count(), 2);

  mock.get_size(32, "hola", nullptr);
  EXPECT_EQ(mock.get_size.count(), 1);

  mock.get_size();
  EXPECT_EQ(mock.get_size.count(), 2);
}

TEST(spy_fn_mocks_return, return_mocks_evaluate_function)
{
  EXPECT_EQ(some_mock{"hello"}.get_name(), "hello");
  EXPECT_EQ(some_mock{"john"}.get_name(), "john");
}

TEST(spy_fn_mocks_function, function_mocks_evaluate_function)
{
  EXPECT_EQ(some_mock{"hello"}.sumate(32, 42), 74);
}

TEST(spy_fn_mocks_function, function_mocks_dont_take_arbitrary_arguments)
{
  // Doesn't compile, this returns one argument too many.
  //
  //   EXPECT_EQ(some_mock{"hello"}.sumate(32, 42, 12), nullptr);
}

TEST(spy_fn, trivial_spy_factory)
{
  auto s = spy();
  EXPECT_EQ(s.count(), 0);

  s();
  EXPECT_EQ(s.count(), 1);

  s();
  EXPECT_EQ(s.count(), 2);
}

TEST(spy_fn, spy_factory_with_function)
{
  auto s = spy([] (int x) { return x + 42; });
  EXPECT_EQ(s.count(), 0);

  EXPECT_EQ(s(12), 54);
  EXPECT_EQ(s.count(), 1);

  EXPECT_EQ(s(1), 43);
  EXPECT_EQ(s.count(), 2);
}

TEST(spy_fn, copied_spies_share_state)
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

struct another_mock
{
  template <typename Signature>
  using mock = std::function<Signature>;

  mock<void()> do_stuff = [] {};
  mock<int()> get_size = [] {
    return int{};
  };
  mock<std::string()> get_name = [this] {
    return this->name_;
  };
  mock<int(float, float)> sumate = [](float a, float b) {
    return a + b;
  };

  explicit another_mock(std::string name = "noone")
    : name_(name)
  {}

private:
  std::string name_;
};

} // namespace

TEST(spy_on, dynamically_spy_on_function)
{
  auto orig = std::function<int()> {[] { return 42; }};
  auto s = spy_on(orig);
  EXPECT_EQ(s.count(), 0);

  EXPECT_EQ(orig(), 42);
  EXPECT_EQ(s.count(), 1);
}

TEST(spy_on, dynamically_spy_on_function_twice)
{
  auto orig = std::function<int()> {[] { return 42; }};
  auto s1 = spy_on(orig);

  orig();
  EXPECT_EQ(s1.count(), 1);

  auto s2 = spy_on(orig);
  orig();
  EXPECT_EQ(s2.count(), 1);
  EXPECT_EQ(s1.count(), 2);
}

TEST(spy_on, scoped_replacement)
{
  auto orig = std::function<int()> {[] { return 42; }};

  {
    auto s1 = spy_on(orig, []{ return 26; });
    EXPECT_EQ(orig(), 26);
    EXPECT_EQ(s1.count(), 1);
  }

  EXPECT_EQ(orig(), 42);
}

TEST(spy_on, realisitc_example_of_dynamic_mocking_with_replacement_method)
{
  auto mock = another_mock {};

  auto s1 = spy_on(mock.sumate);
  EXPECT_EQ(mock.sumate(2, 2), 4);
  EXPECT_EQ(s1.count(), 1);

  auto s2 = spy_on(mock.get_name, [] {
      return "fixed";
    });
  EXPECT_EQ(mock.get_name(), "fixed");
  EXPECT_EQ(s2.count(), 1);
}

} // namespace testing
} // namespace atria
