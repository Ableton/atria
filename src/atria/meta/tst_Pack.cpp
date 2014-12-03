// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/meta/Pack.hpp>
#include <atria/testing/gtest.hpp>
#include <ableton/build_system/Warnings.hpp>
ABL_DISABLE_WARNINGS
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
ABL_RESTORE_WARNINGS

#include <type_traits>

namespace atria {
namespace meta {

TEST(Pack, CanBeUsedAsMPLSequence)
{
  using std::is_same;
  using namespace boost::mpl;
  using SomePack = Pack<int, char, bool>;

ABL_DISABLE_WARNINGS
  BOOST_MPL_ASSERT((is_same<front<SomePack>::type,
                            int>));
  BOOST_MPL_ASSERT_RELATION(size<SomePack>::type::value, ==, 3);
  BOOST_MPL_ASSERT((is_same<pop_front<SomePack>::type,
                            Pack<char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_front<SomePack, unsigned>::type,
                            Pack<unsigned, int, char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_back<SomePack, unsigned>::type,
                            Pack<int, char, bool, unsigned>>));
  BOOST_MPL_ASSERT_RELATION(empty<SomePack>::type::value, ==, false);
#if 0 // not implemented
  BOOST_MPL_ASSERT((is_same<at_c<SomePack, 0>::type,
                            int>));
  BOOST_MPL_ASSERT((is_same<at_c<SomePack, 1>::type,
                            char>));
  BOOST_MPL_ASSERT((is_same<back<SomePack>::type,
                            bool>));
#endif
  BOOST_MPL_ASSERT((is_same<clear<SomePack>::type,
                            Pack<>>));
#if 0 // not implemented
  BOOST_MPL_ASSERT((is_same<pop_back<SomePack>::type,
                            Pack<int, char>>));
#endif
  BOOST_MPL_ASSERT((contains<SomePack, int>));
  BOOST_MPL_ASSERT((contains<SomePack, char>));
  BOOST_MPL_ASSERT((contains<SomePack, bool>));
  BOOST_MPL_ASSERT_NOT((contains<SomePack, unsigned>));
ABL_RESTORE_WARNINGS
}

} // namespace meta
} // namespace atria
