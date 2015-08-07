// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/meta/get_index_sequence.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace meta {

TEST(get_index_sequence, tuple)
{
  static_assert(std::is_same<get_index_sequence<std::tuple<> >,
                             estd::make_index_sequence<0> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::tuple<int> >,
                             estd::make_index_sequence<1> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::tuple<int, double> >,
                             estd::make_index_sequence<2> >{}, "");
}

TEST(get_index_sequence, pair)
{
  static_assert(std::is_same<get_index_sequence<std::pair<int, char> >,
                             estd::make_index_sequence<2> >{}, "");
}

TEST(get_index_sequence, array)
{
  static_assert(std::is_same<get_index_sequence<std::array<int, 0> >,
                             estd::make_index_sequence<0> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::array<int, 1> >,
                             estd::make_index_sequence<1> >{}, "");
  static_assert(std::is_same<get_index_sequence<std::array<int, 10> >,
                             estd::make_index_sequence<10> >{}, "");
}

namespace {

struct custom {};

template <std::size_t N>
auto get(const custom& c)
  -> estd::enable_if_t<(N < 3), int>;

} // anonymous namespace

TEST(get_index_sequence, custom)
{
  static_assert(std::is_same<get_index_sequence<custom>,
                             estd::make_index_sequence<3> >{}, "");
}

namespace {

struct errorish {};

} // anonymous namesapce

TEST(get_index_sequence, error)
{
  static_assert(std::is_same<get_index_sequence<errorish>,
                             could_not_get_index_sequence>{}, "");
  static_assert(std::is_same<get_index_sequence<int>,
                             could_not_get_index_sequence>{}, "");
}

} // namespace meta
} // namespace atria
