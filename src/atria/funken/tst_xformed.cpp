// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/funken/commit.hpp>
#include <atria/funken/state.hpp>
#include <atria/funken/structure.hpp>
#include <atria/funken/watch.hpp>
#include <atria/funken/xformed.hpp>

#include <atria/xform/transducer/filter.hpp>

#include <atria/testing/gtest.hpp>
#include <array>
#include <map>

namespace atria {
namespace funken {

using namespace xform;

TEST(xformed, concepts)
{
  EXPECT_TRUE(meta::check<In_value_spec(
                decltype(xformed(identity, make_state(0))))>());
  EXPECT_TRUE(meta::check<Inout_value_spec(
                decltype(xformed(identity, identity, make_state(0))))>());
  EXPECT_FALSE(Out_value<decltype(xformed(identity, make_state(0)))>());
}

TEST(xformed, to_in)
{
  input<int> i = in(xformed(identity, make_state(0)));
  // This is on the other hand explicitly forbidden
  //   input<int> in2 = xformed(identity, make_state(0));
}

TEST(xformed, identity)
{
  auto s = state<int> { 42 };
  auto x = xformed(identity, s);
  EXPECT_EQ(x.get(), 42);
}

TEST(xformed, identity_two_args_is_zipping)
{
  auto s1 = state<int> { 42 };
  auto s2 = state<int> { 13 };
  auto x = xformed(identity, s1, s2);
  EXPECT_EQ(x.get(), std::make_tuple(42, 13));
}

TEST(xformed, one_arg_mapping)
{
  auto s = state<int> { 42 };
  auto x = xformed(map([] (int a) { return a + 1; }), s);
  EXPECT_EQ(x.get(), 43);
}

TEST(xformed, two_arg_mapping)
{
  auto s1 = state<int> { 42 };
  auto s2 = state<int> { 10 };
  auto x = xformed(map(std::plus<int> {}), s1, s2);
  EXPECT_EQ(x.get(), 52);
}

TEST(xformed, one_arg_filter_with_value)
{
  auto s = state<int> { 42 };
  auto x = xformed(filter([] (int a) { return a % 2 == 0; }), s);
  EXPECT_EQ(x.get(), 42);
}

TEST(xformed, one_arg_filter_without_value)
{
  auto s = state<int> { 43 };
  auto x = xformed(filter([] (int a) { return a % 2 == 0; }), s);
  EXPECT_EQ(x.get(), 0);
}

struct non_default {
  int v = 0;
  non_default() = delete;
  non_default(int v_) : v(v_) {}
  bool operator==(non_default x) const { return v == x.v; }
  bool operator!=(non_default x) const { return v != x.v; }
};

TEST(xformed, one_arg_filter_without_value_non_default_ctr)
{
  auto s = state<non_default>{ non_default{ 43 } };
  EXPECT_THROW(xformed(filter([] (non_default x) { return x.v % 2 == 0; }), s),
               no_value_error);
}

TEST(xformed, one_arg_filter_without_value_non_default_ctr_ok_if_first_value_passes)
{
  auto s = state<non_default>{ 42 };
  auto x = xformed(filter([] (non_default a) { return a.v % 2 == 0; }), s);
  s.set(non_default{43});
  commit(s);
  EXPECT_EQ(x.get().v, 42); // old value still visible

  s.set(non_default{44});
  commit(s);
  EXPECT_EQ(x.get().v, 44); // new value passes
}

TEST(xformed, identity_setter)
{
  auto s = state<int> { 42 };
  auto x = xformed(identity, identity, s);
  EXPECT_EQ(x.get(), 42);

  x.set(5);
  EXPECT_EQ(x.get(), 42);
  EXPECT_EQ(s.get(), 42);

  commit(s);
  EXPECT_EQ(x.get(), 5);
  EXPECT_EQ(s.get(), 5);
}

TEST(xformed, identity_setter_two_parents)
{
  auto s1 = state<int> { 42 };
  auto s2 = state<int> { 12 };

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

TEST(xformed, mapping)
{
  auto st = make_state(0);
  auto x = xformed(map([] (int a) { return a + 2; }), st);
  EXPECT_EQ(2, x.get());

  st.set(42);
  commit(st);
  EXPECT_EQ(44, x.get());
}

TEST(xformed, bidirectional)
{
  auto st = make_state(0);
  auto x = xformed(map([] (int a) { return a + 2; }),
                   map([] (int a) { return a - 2; }),
                   st);
  EXPECT_EQ(2, x.get());

  x.set(42);
  commit(st);
  EXPECT_EQ(42, x.get());
  EXPECT_EQ(40, st.get());
}

TEST(atted, accessing_keys_of_acontainer)
{
  using map_t = std::map<std::string, int>;
  auto st = make_state(map_t{});
  auto x = atted("john", st);
  EXPECT_EQ(0, x.get()); // not found => default constructed

  x.set(12);
  commit(st);
  EXPECT_EQ(0, x.get()); // not magically created
  EXPECT_EQ(map_t{}, st.get());

  st.set(map_t{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get()); // at last, I found it!

  x.set(43);
  commit(st);
  EXPECT_EQ(43, x.get()); // happy birthday, john!
  EXPECT_EQ((map_t{{ "john", 43 }}), st.get());

  st.set(map_t{{}});
  commit(st);
  EXPECT_EQ(43, x.get()); // Simply doesn't update
}

TEST(atted, accessing_keys_of_acontainer_in_version)
{
  using map_t = std::map<std::string, int>;
  auto st = make_state(map_t{});
  auto x = atted("john", st);
  EXPECT_EQ(0, x.get()); // not found => default constructed

  st.set(map_t{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get()); // at last, I found it!

  x.set(43); // Should not compile!
}

TEST(atted, atted_from_erased_inoutput)
{
  using map_t = std::map<std::string, int>;
  auto st = make_state(map_t{});
  auto x = atted("john", inoutput<map_t>{inout(st)});
  st.set(map_t{{ "john", 42 }});
  commit(st);
  EXPECT_EQ(42, x.get());
}

namespace {

struct person
{
  std::string name;
  std::size_t age;

  bool operator==(const person& x) const
  { return name == x.name && age == x.age; }
  bool operator!=(const person& x) const
  { return !(*this == x); }
};

} // namespace


TEST(atted, updates_dont_overwrite_new_data_in_complex_scenario)
{
  auto st = make_state(std::array<person, 2> {{
        { "john", 42 },
        { "emil", 2 }
      }});
  auto x1 = atted(0u, st);
  auto x2 = atted(1u, xformed(identity, identity, st));
  auto x3 = atted(1u, st);
  auto x4 = attred(&person::name, x2);
  auto x5 = attred(&person::age, x3);
  auto x6 = attred(&person::age, x1);

  x6.set(43u);
  x5.set(3u);
  x4.set("emily");
  commit(st);

  EXPECT_EQ(st.get(), (std::array<person, 2> {{
          { "john",  43 },
          { "emily", 3 }
        }}));
  EXPECT_EQ(x6.get(), 43);
  EXPECT_EQ(x4.get(), "emily");
  EXPECT_EQ(x5.get(), 3);
}

TEST(atted, accesing_attributes)
{
  auto st = make_state(person { "john", 42 });
  auto x = attred(&person::age, st);
  EXPECT_EQ(42, x.get());

  x.set(43u);
  commit(st);
  EXPECT_EQ(43, x.get()); // Happy birthday John!
  EXPECT_EQ((person{ "john", 43 }), st.get());
}

TEST(atted, accesing_attributes_in_version)
{
  auto st = make_state(person { "john", 42 });
  auto x = attred(&person::age, in(st));
  EXPECT_EQ(42, x.get());

  // Should not compile!
  // x.set(43);
}

struct machine : structure<machine>
{
  std::string name;
  std::size_t wheels;

  machine(std::string name_ = "",
          std::size_t wheels_ = 0)
    : name(name_), wheels(wheels_) {}
};

} // namespace funken
} // namespace atria

ABL_FUNKEN_STRUCT(
  atria::funken::machine,
  (std::string, name)
  (std::size_t, wheels))

namespace atria {
namespace funken {

TEST(atted, modifying_attributes_of_immutable)
{
  auto st = make_state(machine { "car", 4 });
  auto x = attred(&machine::name, st);
  auto y = attred(&machine::wheels, st);

  y.set(3u);
  commit(st);
  EXPECT_EQ(st.get(), (machine { "car", 3 }));
  EXPECT_EQ(x.get(), "car");
  EXPECT_EQ(y.get(), 3);

  x.set("tricar");
  commit(st);
  EXPECT_EQ(st.get(), (machine { "tricar", 3 }));
  EXPECT_EQ(x.get(), "tricar");
  EXPECT_EQ(y.get(), 3);
}

} // namespace funken
} // namespace atria
