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
