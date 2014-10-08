// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/base/variant/Match.hpp>
#include <ableton/testing/Spies.hpp>
#include <ableton/testing/gtest.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
ABL_RESTORE_WARNINGS
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

  void resetName()
  {
    mName = "resetted";
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
    [] (const Person& x) { return x.name(); },
    [] (const std::string& x) { return x; },
    [] (int x) { return boost::lexical_cast<std::string>(x); });

  EXPECT_EQ(result, "42");
}

TEST(Match, CanUseBindedFunctions)
{
  using namespace std::placeholders;

  using Number = boost::variant<int, double>;

  auto result = match(
    Number(42.5),
    when<double>(std::bind(&boost::lexical_cast<std::string, double>, _1)),
    when<int>(std::bind(&boost::lexical_cast<std::string, int>, _1)));

  EXPECT_EQ(result, "42.5");
}

struct BadPerson : Person {
  using Person::Person;
  std::string doBadThing() const { return ":("; }
};

struct GoodPerson : Person{
  using Person::Person;
  std::string doGoodThing() const { return ":)"; }
};

using People = boost::variant<GoodPerson, BadPerson>;

TEST(Match, CanUseMemberFunctions)
{
  auto result = match(
     People { GoodPerson { "John" } },
     when<GoodPerson>(std::mem_fn(&GoodPerson::doGoodThing)),
     when<BadPerson>(std::mem_fn(&BadPerson::doBadThing)));

  EXPECT_EQ(result, ":)");
}

TEST(Match, PolymorphicExampleWithBaseClass)
{
  auto person = People { GoodPerson { "John" } };
  auto name = match(
    person,
    when<Person>(std::mem_fn(&Person::name)));

  EXPECT_EQ(name, "John");
}

TEST(Match, ExplicitResultTypeForCaseWhereDeductionFails)
{
  auto person = People { GoodPerson { "John" } };

  auto name = match(
    person,
    otherwise<std::string>(std::mem_fn(&Person::name)));
  EXPECT_EQ(name, "John");

  match(
    person,
    otherwise(std::mem_fn(&Person::resetName)));

  auto newName = match(
    person,
    otherwise<std::string>(std::mem_fn(&Person::name)));
  EXPECT_EQ(newName, "resetted");
}

TEST(Match, OtherwiseCanBeUsedAsCatchAll)
{
  auto person = People { GoodPerson { "John" } };

  match(
    person,
    otherwise());

  auto name = match(
    person,
    otherwise<std::string>());
  EXPECT_EQ(name, "");
}

TEST(Match, TotallyIncompatibleReturnTypesCanBeUsed)
{
  auto person = People { GoodPerson { "John" } };

  match(
    person,
    [] (BadPerson)  { return std::string(); },
    [] (GoodPerson) { return int(); });
}

TEST(Match, TotallyIncompatibleReturnTypesCanBeUsedAndOneCanBeVoid)
{
  auto person = People { GoodPerson { "John" } };

  match(
    person,
    [] (BadPerson)  { return std::string(); },
    [] (GoodPerson) {});
}

} // anonymous namespace

} // namespace variant
} // namespace base
} // namespace ableton
