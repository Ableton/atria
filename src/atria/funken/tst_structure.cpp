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

#include <atria/funken/structure.hpp>
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

struct person : structure<person>
{
  std::string name;
  std::size_t age;

  person(std::string name_ = "",
         std::size_t age_  = 0)
    : name(name_), age(age_) {}
};

} // namespace test
} // namespace funken
} // namespace atria

ABL_FUNKEN_STRUCT(
  atria::funken::test::person,
  (std::string, name)
  (std::size_t, age))

namespace atria {
namespace funken {

TEST(structure, can_put_in_hash_map)
{
  using test::person;
  std::unordered_set<person> s;
  s.insert(person { "peter", 42 });
  EXPECT_EQ(1, s.count(person { "peter", 42 }));
  EXPECT_EQ(0, s.count(person { "peter", 13 }));
  EXPECT_EQ(0, s.count(person { "john", 42 }));
}

TEST(structure, can_put_in_map)
{
  using test::person;
  std::set<person> s;
  s.insert(person { "peter", 42 });
  EXPECT_EQ(1, s.count(person { "peter", 42 }));
  EXPECT_EQ(0, s.count(person { "peter", 13 }));
  EXPECT_EQ(0, s.count(person { "john", 42 }));
}

TEST(structure, invalidate_cache)
{
  using test::person;
  auto x = person { "john", 13 };
  auto y = person { "peter", 13 };
  EXPECT_TRUE(x != y);
  auto z = y;
  z.name = "john";
  EXPECT_FALSE(x == z);
  modified(z);
  EXPECT_TRUE(x == z);
}

} // namespace funken
} // namespace atria
