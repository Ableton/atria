// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/into_vector.hpp>
#include <atria/xform/transducer/chain.hpp>
#include <atria/xform/transducer/take.hpp>
#include <atria/prelude/comp.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(chain, append)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5 }));
}

TEST(chain, variadic)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2, v1), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5, 1, 2 }));
}

TEST(chain, no_chaining_if_no_input)
{
  // Again, this is a limitation of the current approach to pure
  // stateful transducers
  auto v1 = std::vector<int> {};
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chain(v2), v1);
  EXPECT_EQ(res, (std::vector<int> {}));
}

TEST(chainl, prepend)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2), v1);
  EXPECT_EQ(res, (std::vector<int> { 13, 42, 5, 1, 2 }));
}

TEST(chainl, variadic)
{
  auto v1 = std::vector<int> { 1, 2 };
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2, v1), v1);
  EXPECT_EQ(res, (std::vector<int> { 1, 2, 13, 42, 5, 1, 2 }));
}

TEST(chainl, no_chaining_if_no_input)
{
  // Again, this is a limitation of the current approach to pure
  // stateful transducers
  auto v1 = std::vector<int> {};
  auto v2 = std::vector<int> { 13, 42, 5 };
  auto res = into_vector(chainl(v2), v1);
  EXPECT_EQ(res, (std::vector<int> {}));
}

} // namespace xform
} // namespace atria
