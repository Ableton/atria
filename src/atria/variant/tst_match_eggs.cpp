// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/variant/match_eggs.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <eggs/variant.hpp>
#include <boost/lexical_cast.hpp>
ABL_RESTORE_WARNINGS
#include <functional>

namespace atria {
namespace variant {

namespace {

struct person
{
  std::string name_;

  std::string name() const
  {
    return name_;
  }
};

using thing = eggs::variant<person, std::string, int>;

bool operator==(const person& a, const person& b)
{
  return a.name() == b.name();
}

TEST(match_eggs, can_be_used_with_lambdas_and_rvalues)
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

TEST(match_eggs, can_mutate_visited)
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

TEST(match_eggs, can_return_something)
{
  auto sth = thing(42);
  auto result = match(
    sth,
    [] (const person& x) { return x.name(); },
    [] (const std::string& x) { return x; },
    [] (int x) { return boost::lexical_cast<std::string>(x); });

  EXPECT_EQ(result, "42");
}

} // anonymous namespace

} // namespace variant
} // namespace atria
