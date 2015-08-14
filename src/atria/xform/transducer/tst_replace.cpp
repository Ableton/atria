// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/transduce.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/replace.hpp>
#include <atria/estd/functional.hpp>
#include <atria/testing/gtest.hpp>
#include <map>

namespace atria {
namespace xform {

TEST(replace, replace)
{
  auto table = std::map<std::string, std::string> {
    {"hola", "adios"}};
  auto v = std::vector<std::string> {
    "hola", " ", "amigo"};

  EXPECT_EQ(transduce(replace(table),
                      estd::plus<>{},
                      std::string{},
                      v),
            "adios amigo");
}

TEST(replace, replace_variadic)
{
  using tup = std::tuple<int, std::string>;

  auto table = std::map<tup, tup> {
    {tup(1, "hola"), tup(42, "adios")}};

  auto v1 = std::vector<int> { 1, 2, 3 };
  auto v2 = std::vector<std::string> {"hola", " ", "amigo"};

  auto res = into_vector(replace(table), v1, v2);
  EXPECT_EQ(res, (decltype(res) {
        tup(42, "adios"),
        tup(2, " "),
        tup(3, "amigo")
      }));
}

TEST(replace, replace_all)
{
  auto table = std::map<std::string, int> {
    {"hola", 12},
    {"amigo", 42}};
  auto v = std::vector<std::string> {
    "hola", " ", "amigo"};

  EXPECT_EQ(transduce(replace_all(table),
                      estd::plus<>{},
                      int{},
                      v),
            54);
}

TEST(replace, replace_safe_pass)
{
  auto table = std::map<std::string, int> {
    {"hola", 12},
    {"amigo", 42}};
  auto v = std::vector<std::string> {
    "hola", "amigo"};

  EXPECT_EQ(transduce(replace_all_safe(table),
                      estd::plus<>{},
                      int{},
                      v),
            54);
}


TEST(replace, replace_safe_exception)
{
  auto table = std::map<std::string, int> {
    {"hola", 12},
    {"amigo", 42}};
  auto v = std::vector<std::string> {
    "hola", "oops", "amigo"};

  EXPECT_THROW(
      transduce(replace_all_safe(table),
                estd::plus<>{},
                int{},
                v),
      std::out_of_range);
}

} // namespace xform
} // namespace atria
