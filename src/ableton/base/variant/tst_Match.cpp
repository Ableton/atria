// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/base/variant/Match.hpp>
#include <ableton/testing/Spies.hpp>
#include <gtest/gtest.h>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
#include <functional>

namespace ableton {
namespace base {
namespace variant {

class Person
{
public:
  Person(std::string name)
    : mName(std::move(name))
  {}

  std::string name() const
  {
    return mName;
  }

private:
  std::string mName;
};

using Thing = boost::variant<Person, std::string, int>;

bool operator==(const Person& a, const Person& b)
{
  return a.name() == b.name();
}

std::ostream& operator<<(std::ostream& os, const Person& b)
{
  return os << "Person: " << b.name();
}

namespace {

TEST(Match, CanBeUsedWithLambdasAndRValues)
{
  auto f = testing::spy();

  match(
    Thing(42),
    [] (const Person& x) {
      throw std::exception();
    },
    [] (const std::string& x) {
      throw std::exception();
    },
    [&f] (int x) {
      f();
    });

  EXPECT_EQ(f.count(), 1);
}

TEST(Match, CanMutateVisited)
{
  auto thing = Thing(42);

  match(
    thing,
    [] (const Person& x) {},
    [] (const std::string& x) {},
    [] (int& x) {
      x = 21;
    });

  EXPECT_EQ(thing, Thing(21));
}

TEST(Match, CanReturnSomething)
{
  auto thing = Thing(42);
  auto result = match(
    thing,
    [] (const Person& x) -> std::string { return x.name(); },
    [] (const std::string& x) -> std::string { return x; },
    [] (int x) -> std::string { return boost::lexical_cast<std::string>(x); });

  EXPECT_EQ(result, "42");
}

TEST(Match, CanUseBindedFunctions)
{
  using namespace std::placeholders;

  using Number = boost::variant<int, double>;

  auto result = match(
    Number(42.5),
    std::bind(&boost::lexical_cast<std::string, int>, _1),
    // [jbo] The following line cause a compilation error when
    // replaced by:
    //
    //    std::bind(&boost::lexical_cast<std::string, double>, _1)
    //
    // This is so because the binder functor is templated over the
    // arguments, so the visitor call becomes ambiguous.
    [](double x) { return boost::lexical_cast<std::string>(x); }
    );

  EXPECT_EQ(result, "42.5");
}

struct BadPerson : Person {
  using Person::Person;
  std::string doBadThing() const { return ":("; };
};

struct GoodPerson : Person{
  using Person::Person;
  std::string doGoodThing() const { return ":)"; };
};

using People = boost::variant<GoodPerson, BadPerson>;

TEST(Match, CanUseMemberFunctions)
{
  auto result = match(
    People { GoodPerson { "John" } },
    // [jbo] This is is added just so it finds the correct type, since
    // std::result_of seems to fail for the result of std::mem_fn.
    [](std::nullptr_t) { return std::string(); },

    std::mem_fn(&GoodPerson::doGoodThing),

    // [jbo] Like with bind(), having more than one of these turns the
    // whole thing ambiguous... so sad :(
    //
    //     std::mem_fn(&BadPerson::doBadThing)
    //
    [](const BadPerson& p) { return p.doBadThing(); }
    );

  EXPECT_EQ(result, ":)");
}

} // anonymous namespace

} // namespace variant
} // namespace base
} // namespace ableton
