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
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/take_while.hpp>
#include <atria/xform/transducer/map.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/estd/functional.hpp>

#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(take_while, concept)
{
  using namespace std::placeholders;
  meta::check<Transparent_transducer_spec(
    decltype(take_while(std::bind(estd::less<>{}, 42, _1))))>();
}

TEST(take_while, into)
{
  using namespace std::placeholders;
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  auto pred = std::bind(estd::less<>{}, _1, 4);

  auto res = into_vector(take_while(pred), v);
  EXPECT_EQ(res, (decltype(res) { 1, 2, 3 }));
}

namespace {
bool free_lt4(int x) { return x < 4; }
} // anonymous

TEST(take_while, invoke)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 3 };
  auto res = into_vector(take_while(free_lt4), v);
  EXPECT_EQ(res, (decltype(res) { 1, 2, 3 }));
}

TEST(take_while, generate_with_map)
{
  auto count = int{};
  auto counter = [&]() mutable { return count++; };
  auto lt10 = [] (int x) { return x < 10; };
  auto res = transduce(
    comp(map(counter), take_while(lt10)),
    std::plus<int>{},
    1);
  EXPECT_EQ(res, 46);
}

} // namespace xform
} // namespace atria
