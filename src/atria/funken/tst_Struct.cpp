// Copyright: 2014, Ableton AG, Berlin. All rights reserved.


#include <atria/funken/Struct.hpp>
#include <atria/testing/gtest.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
#include <boost/fusion/include/adapt_struct.hpp>
ABL_RESTORE_WARNINGS
#include <iostream>
#include <unordered_set>
#include <string>

namespace atria {
namespace funken {
namespace test {

struct Person : Struct<Person>
{
  std::string name;
  std::size_t age;

  Person(std::string name = "",
         std::size_t age  = 0)
    : name(name), age(age) {}
};

} // namespace test
} // namespace funken
} // namespace atria

ABL_FUNKEN_STRUCT(
  atria::funken::test::Person,
  (std::string, name)
  (std::size_t, age))

namespace atria {
namespace funken {

TEST(Struct, CanPutInHashMap)
{
  using test::Person;
  std::unordered_set<Person> s;
  s.insert(Person { "peter", 42 });
  EXPECT_EQ(1, s.count(Person { "peter", 42 }));
  EXPECT_EQ(0, s.count(Person { "peter", 13 }));
  EXPECT_EQ(0, s.count(Person { "john", 42 }));
}

TEST(Struct, CanPutInMap)
{
  using test::Person;
  std::set<Person> s;
  s.insert(Person { "peter", 42 });
  EXPECT_EQ(1, s.count(Person { "peter", 42 }));
  EXPECT_EQ(0, s.count(Person { "peter", 13 }));
  EXPECT_EQ(0, s.count(Person { "john", 42 }));
}

TEST(Struct, InvalidateCache)
{
  using test::Person;
  auto x = Person { "john", 13 };
  auto y = Person { "peter", 13 };
  EXPECT_TRUE(x != y);
  auto z = y;
  z.name = "john";
  EXPECT_FALSE(x == z);
  modified(z);
  EXPECT_TRUE(x == z);
}

} // namespace funken
} // namespace atria
