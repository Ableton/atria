// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/funken/Commit.hpp>
#include <ableton/funken/State.hpp>
#include <ableton/funken/Struct.hpp>
#include <ableton/funken/Watch.hpp>
#include <ableton/funken/Xformed.hpp>
#include <ableton/testing/gtest.hpp>
#include <array>
#include <map>

namespace ableton {
namespace funken {

using namespace xform;

TEST(Xformed, Concepts)
{
  EXPECT_TRUE(meta::check<In_value<
              decltype(xformed(identity, state(0)))>>());
  EXPECT_TRUE(meta::check<Inout_value<
              decltype(xformed(identity, identity, state(0)))>>());
  EXPECT_FALSE(Out_value<decltype(xformed(identity, state(0)))>());
}

TEST(Xformed, ToIn)
{
  In<int> i = in(xformed(identity, state(0)));
  // This is on the other hand explicitly forbidden
  //   In<int> in2 = xformed(identity, state(0));
}

TEST(Xformed, Identity)
{
  auto s = State<int> { 42 };
  auto x = xformed(identity, s);
  EXPECT_EQ(x.get(), 42);
}

TEST(Xformed, IdentityTwoArgsIsZipping)
{
  auto s1 = State<int> { 42 };
  auto s2 = State<int> { 13 };
  auto x = xformed(identity, s1, s2);
  EXPECT_EQ(x.get(), std::make_tuple(42, 13));
}

TEST(Xformed, OneArgMapping)
{
  auto s = State<int> { 42 };
  auto x = xformed(map([] (int x) { return x + 1; }), s);
  EXPECT_EQ(x.get(), 43);
}

TEST(Xformed, TwoArgMapping)
{
  auto s1 = State<int> { 42 };
  auto s2 = State<int> { 10 };
  auto x = xformed(map(std::plus<int> {}), s1, s2);
  EXPECT_EQ(x.get(), 52);
}

TEST(Xformed, OneArgFilterWithValue)
{
  auto s = State<int> { 42 };
  auto x = xformed(filter([] (int x) { return x % 2 == 0; }), s);
  EXPECT_EQ(x.get(), 42);
}

TEST(Xformed, OneArgFilterWithoutValue)
{
  auto s = State<int> { 43 };
  auto x = xformed(filter([] (int x) { return x % 2 == 0; }), s);
  EXPECT_EQ(x.get(), 0);
}

struct NonDefault {
  int v = 0;
  NonDefault() = delete;
  NonDefault(int v) : v(v) {}
  bool operator==(NonDefault x) const { return v == x.v; }
  bool operator!=(NonDefault x) const { return v != x.v; }
};

TEST(Xformed, OneArgFilterWithoutValueNonDefaultCtr)
{
  auto s = State<NonDefault>{ NonDefault{ 43 } };
  EXPECT_THROW(xformed(filter([] (NonDefault x) { return x.v % 2 == 0; }), s),
               NoValueError);
}

TEST(Xformed, OneArgFilterWithoutValueNonDefaultCtrOkIfFirstValuePasses)
{
  auto s = State<NonDefault>{ 42 };
  auto x = xformed(filter([] (NonDefault x) { return x.v % 2 == 0; }), s);
  s.set(NonDefault{43});
  commit(s);
  EXPECT_EQ(x.get().v, 42); // old value still visible

  s.set(NonDefault{44});
  commit(s);
  EXPECT_EQ(x.get().v, 44); // new value passes
}

TEST(Xformed, IdentitySetter)
{
  auto s = State<int> { 42 };
  auto x = xformed(identity, identity, s);
  EXPECT_EQ(x.get(), 42);

  x.set(5);
  EXPECT_EQ(x.get(), 42);
  EXPECT_EQ(s.get(), 42);

  commit(s);
  EXPECT_EQ(x.get(), 5);
  EXPECT_EQ(s.get(), 5);
}

TEST(Xformed, IdentitySetterTwoParents)
{
  auto s1 = State<int> { 42 };
  auto s2 = State<int> { 12 };

  auto x = xformed(identity, identity, s1, s2);
  EXPECT_EQ(x.get(), std::make_tuple(42, 12));

  x.set(std::make_tuple(5, 12));
  EXPECT_EQ(x.get(), std::make_tuple(42, 12));
  EXPECT_EQ(s1.get(), 42);
  EXPECT_EQ(s2.get(), 12);

  commit(s1, s2);
  EXPECT_EQ(x.get(), std::make_tuple(5, 12));
  EXPECT_EQ(s1.get(), 5);
  EXPECT_EQ(s2.get(), 12);
}

TEST(Xformed, Mapping)
{
  auto st = state(0);
  auto x = xformed(map([] (int x) { return x + 2; }), st);
  EXPECT_EQ(2, x.get());

  st.set(42);
  commit(st);
  EXPECT_EQ(44, x.get());
}

TEST(Xformed, Bidirectional)
{
  auto st = state(0);
  auto x = xformed(map([] (int x) { return x + 2; }),
                   map([] (int x) { return x - 2; }),
                   st);
  EXPECT_EQ(2, x.get());

  x.set(42);
  commit(st);
  EXPECT_EQ(42, x.get());
  EXPECT_EQ(40, st.get());
}

TEST(Atted, AccessingKeysOfAContainer)
{
  using MapT = std::map<std::string, int>;
  auto st = state(MapT{});
  auto x = atted("john", st);
  EXPECT_EQ(0, x.get()); // not found => default constructed

  x.set(12);
  commit(st);
  EXPECT_EQ(0, x.get()); // not magically created
  EXPECT_EQ(MapT{}, st.get());

  st.set(MapT{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get()); // at last, I found it!

  x.set(43);
  commit(st);
  EXPECT_EQ(43, x.get()); // happy birthday, john!
  EXPECT_EQ((MapT{{ "john", 43 }}), st.get());

  st.set(MapT{{}});
  commit(st);
  EXPECT_EQ(43, x.get()); // Simply doesn't update
}

TEST(Atted, AccessingKeysOfAContainerInVersion)
{
  using MapT = std::map<std::string, int>;
  auto st = state(MapT{});
  auto x = atted("john", st);
  EXPECT_EQ(0, x.get()); // not found => default constructed

  st.set(MapT{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get()); // at last, I found it!

  x.set(43); // Should not compile!
}

TEST(Atted, AttedFromErasedInout)
{
  using MapT = std::map<std::string, int>;
  auto st = state(MapT{});
  auto x = atted("john", Inout<MapT>{inout(st)});
  st.set(MapT{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get());
}

namespace {

struct Person
{
  std::string name;
  std::size_t age;

  bool operator==(const Person& x) const
  { return name == x.name && age == x.age; }
  bool operator!=(const Person& x) const
  { return !(*this == x); }
};

} // namespace


TEST(Atted, UpdatesDontOverwriteNewDataInComplexScenario)
{
  auto st = state(std::array<Person, 2> {{
        { "john", 42 },
        { "emil", 2 }
      }});
  auto x1 = atted(0, st);
  auto x2 = atted(1, xformed(identity, identity, st));
  auto x3 = atted(1, st);
  auto x4 = attred(&Person::name, x2);
  auto x5 = attred(&Person::age, x3);
  auto x6 = attred(&Person::age, x1);

  x6.set(43);
  x5.set(3);
  x4.set("emily");
  commit(st);

  EXPECT_EQ(st.get(), (std::array<Person, 2> {{
          { "john",  43 },
          { "emily", 3 }
        }}));
  EXPECT_EQ(x6.get(), 43);
  EXPECT_EQ(x4.get(), "emily");
  EXPECT_EQ(x5.get(), 3);
}

TEST(Atted, AccesingAttributes)
{
  auto st = state(Person { "john", 42 });
  auto x = attred(&Person::age, st);
  EXPECT_EQ(42, x.get());

  x.set(43);
  commit(st);
  EXPECT_EQ(43, x.get()); // Happy birthday John!
  EXPECT_EQ((Person{ "john", 43 }), st.get());
}

TEST(Atted, AccesingAttributesInVersion)
{
  auto st = state(Person { "john", 42 });
  auto x = attred(&Person::age, in(st));
  EXPECT_EQ(42, x.get());

  // Should not compile!
  // x.set(43);
}

struct Machine : Struct<Machine>
{
  std::string name;
  std::size_t wheels;

  Machine(std::string name = "",
          std::size_t wheels = 0)
    : name(name), wheels(wheels) {}
};

} // namespace funken
} // namespace ableton

ABL_FUNKEN_STRUCT(
  ableton::funken::Machine,
  (std::string, name)
  (std::size_t, wheels))

namespace ableton {
namespace funken {

TEST(Atted, ModifyingAttributesOfImmutable)
{
  auto st = state(Machine { "car", 4 });
  auto x = attred(&Machine::name, st);
  auto y = attred(&Machine::wheels, st);

  y.set(3);
  commit(st);
  EXPECT_EQ(st.get(), (Machine { "car", 3 }));
  EXPECT_EQ(x.get(), "car");
  EXPECT_EQ(y.get(), 3);

  x.set("tricar");
  commit(st);
  EXPECT_EQ(st.get(), (Machine { "tricar", 3 }));
  EXPECT_EQ(x.get(), "tricar");
  EXPECT_EQ(y.get(), 3);
}

} // namespace funken
} // namespace ableton
