// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <ableton/meta/StdTuple.hpp>
#include <gtest/gtest.h>

#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/assert.hpp>

#include <type_traits>

namespace ableton {
namespace meta {

TEST(StdTuple, CanBeUsedAsMPLSequence)
{
  using std::is_same;
  using namespace boost::mpl;
  using SomeTuple = std::tuple<int, char, bool>;

  BOOST_MPL_ASSERT((is_same<front<SomeTuple>::type,
                            int>));
  BOOST_MPL_ASSERT_RELATION(size<SomeTuple>::type::value, ==, 3);
  BOOST_MPL_ASSERT((is_same<pop_front<SomeTuple>::type,
                            std::tuple<char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_front<SomeTuple, unsigned>::type,
                            std::tuple<unsigned, int, char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_back<SomeTuple, unsigned>::type,
                            std::tuple<int, char, bool, unsigned>>));
  BOOST_MPL_ASSERT_RELATION(empty<SomeTuple>::type::value, ==, false);
  BOOST_MPL_ASSERT((is_same<at_c<SomeTuple, 0>::type,
                            int>));
  BOOST_MPL_ASSERT((is_same<at_c<SomeTuple, 1>::type,
                            char>));
  BOOST_MPL_ASSERT((is_same<back<SomeTuple>::type,
                            bool>));
  BOOST_MPL_ASSERT((is_same<clear<SomeTuple>::type,
                            std::tuple<>>));
  BOOST_MPL_ASSERT((is_same<pop_back<SomeTuple>::type,
                            std::tuple<int, char>>));
  BOOST_MPL_ASSERT((contains<SomeTuple, int>));
  BOOST_MPL_ASSERT((contains<SomeTuple, char>));
  BOOST_MPL_ASSERT((contains<SomeTuple, bool>));
  BOOST_MPL_ASSERT_NOT((contains<SomeTuple, unsigned>));
}

} // namespace meta
} // namespace ableton
