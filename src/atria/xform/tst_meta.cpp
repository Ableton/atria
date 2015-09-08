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

#include <atria/xform/meta.hpp>
#include <atria/prelude/identity.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(output_of, identity)
{
  using meta::pack;

  static_assert(
    output_of_t<identity_t>{} == pack<>{}, "");
  static_assert(
    output_of_t<identity_t, int>{} == pack<int&&>{}, "");
  static_assert(
    output_of_t<identity_t, int, float>{} == pack<int&&, float&&>{}, "");

  static_assert(
    output_of_t<identity_t, int&>{} == pack<int&>{}, "");
  static_assert(
    output_of_t<identity_t, int&, const float&>{} ==
    pack<int&, const float&>{}, "");

  static_assert(
    output_of_t<identity_t, int&&>{} == pack<int&&>{}, "");
  static_assert(
    output_of_t<identity_t, const int&&, float&&>{} ==
    pack<const int&&, float&&>{}, "");
}

TEST(result_of, identity)
{
  using meta::pack;

  static_assert(
    pack<result_of_t<identity_t> >{} == pack<std::tuple<> >{}, "");
  static_assert(
    pack<result_of_t<identity_t, int> >{} == pack<int>{}, "");
  static_assert(
    pack<result_of_t<identity_t, int, float> >{} ==
    pack<std::tuple<int, float> >{}, "");

  static_assert(
    pack<result_of_t<identity_t, int&> >{} == pack<int>{}, "");
  static_assert(
    pack<result_of_t<identity_t, int&, float&> >{} ==
    pack<std::tuple<int, float> >{}, "");
}

} // namespace xform
} // namespace atria
