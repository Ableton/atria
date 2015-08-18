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

#ifndef ABL_TST_MATCH_VARIANT_TYPE
#error "Must define ABL_TST_MATCH_VARIANT_TYPE"
#endif

#ifndef ABL_TST_MATCH_SUITE_NAME
#error "Must define ABL_TST_MATCH_SUITE_NAME"
#endif

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>
ABL_RESTORE_WARNINGS
#include <functional>

namespace atria {
namespace variant {

namespace {

class person
{
public:
  person(std::string name)
    : name_(std::move(name))
  {}

  std::string name() const
  {
    return name_;
  }

  void resetName()
  {
    name_ = "resetted";
  }

private:
  std::string name_;
};

using thing = ABL_TST_MATCH_VARIANT_TYPE<person, std::string, int>;

bool operator==(const person& a, const person& b)
{
  return a.name() == b.name();
}

#ifdef ABL_TST_MATCH_ENABLE_OUTPUT
std::ostream& operator<<(std::ostream& os, const person& b)
{
  return os << "person: " << b.name();
}
#endif // ABL_TST_MATCH_ENABLE_OUTPUT

TEST(ABL_TST_MATCH_SUITE_NAME, can_be_used_with_lambdas_and_rvalues)
{
  auto f = testing::spy();

  match(
    thing(42),
    [] (const person&) {
      throw std::exception();
    },
    [] (const std::string&) {
      throw std::exception();
    },
    [&f] (int) {
      f();
    });

  EXPECT_EQ(f.count(), 1);
}

TEST(ABL_TST_MATCH_SUITE_NAME, can_mutate_visited)
{
  auto sth = thing(42);

  match(
    sth,
    [] (const person&) {},
    [] (const std::string&) {},
    [] (int& x) {
      x = 21;
    });

  EXPECT_EQ(sth, thing(21));
}

TEST(ABL_TST_MATCH_SUITE_NAME, can_return_something)
{
  auto sth = thing(42);
  auto result = match(
    sth,
    [] (const person& x) { return x.name(); },
    [] (const std::string& x) { return x; },
    [] (int x) { return boost::lexical_cast<std::string>(x); });

  EXPECT_EQ(result, "42");
}

TEST(ABL_TST_MATCH_SUITE_NAME, can_use_binded_functions)
{
  using namespace std::placeholders;

  using number = ABL_TST_MATCH_VARIANT_TYPE<int, double>;

  auto result = match(
    number(42.5),
    when<double>(std::bind(&boost::lexical_cast<std::string, double>, _1)),
    when<int>(std::bind(&boost::lexical_cast<std::string, int>, _1)));

  EXPECT_EQ(result, "42.5");
}

struct bad_person : person {
  using person::person;
  std::string do_bad_thing() const { return ":("; }
};

struct good_person : person{
  using person::person;
  std::string do_good_thing() const { return ":)"; }
};

using people = ABL_TST_MATCH_VARIANT_TYPE<good_person, bad_person>;

TEST(ABL_TST_MATCH_SUITE_NAME, can_use_member_functions)
{
  auto result = match(
     people { good_person { "John" } },
     when<good_person>(std::mem_fn(&good_person::do_good_thing)),
     when<bad_person>(std::mem_fn(&bad_person::do_bad_thing)));

  EXPECT_EQ(result, ":)");
}

TEST(ABL_TST_MATCH_SUITE_NAME, polymorphic_example_with_base_class)
{
  auto someone = people { good_person { "John" } };
  auto name = match(
    someone,
    when<person>(std::mem_fn(&person::name)));

  EXPECT_EQ(name, "John");
}

TEST(ABL_TST_MATCH_SUITE_NAME, explicit_result_type_for_case_where_deduction_fails)
{
  auto person = people { good_person { "John" } };

  auto name = match(
    person,
    otherwise<std::string>(std::mem_fn(&person::name)));
  EXPECT_EQ(name, "John");

  match(
    person,
    otherwise(std::mem_fn(&person::resetName)));

  auto new_name = match(
    person,
    otherwise<std::string>(std::mem_fn(&person::name)));
  EXPECT_EQ(new_name, "resetted");
}

TEST(ABL_TST_MATCH_SUITE_NAME, can_deduce_generic_case)
{
  auto person = people { good_person { "John" } };

  auto name = match(
    person,
    std::mem_fn(&person::name));
  EXPECT_EQ(name, "John");

  match(
    person,
    std::mem_fn(&person::resetName));

  auto new_name = match(
    person,
    std::mem_fn(&person::name));
  EXPECT_EQ(new_name, "resetted");
}

TEST(ABL_TST_MATCH_SUITE_NAME, otherwise_can_be_used_as_catch_all)
{
  auto person = people { good_person { "John" } };

  match(
    person,
    otherwise());

  auto name = match(
    person,
    otherwise<std::string>());
  EXPECT_EQ(name, "");
}

TEST(ABL_TST_MATCH_SUITE_NAME, totally_incompatible_return_types_can_be_used)
{
  auto person = people { good_person { "John" } };

  match(
    person,
    [] (bad_person)  { return std::string(); },
    [] (good_person) { return int(); });
}

TEST(ABL_TST_MATCH_SUITE_NAME, totally_incompatible_return_types_can_be_used_and_one_can_be_void)
{
  auto person = people { good_person { "John" } };

  match(
    person,
    [] (bad_person)  { return std::string(); },
    [] (good_person) {});
}

} // anonymous namespace

} // namespace variant
} // namespace atria
