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

#include <atria/meta/std_tuple.hpp>
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

TEST(std_tuple, can_be_used_as_mplsequence)
{
  using std::is_same;
  using namespace boost::mpl;
  using some_tuple = std::tuple<int, char, bool>;

ABL_DISABLE_WARNINGS
  BOOST_MPL_ASSERT((is_same<front<some_tuple>::type,
                            int>));
  BOOST_MPL_ASSERT_RELATION(size<some_tuple>::type::value, ==, 3);
  BOOST_MPL_ASSERT((is_same<pop_front<some_tuple>::type,
                            std::tuple<char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_front<some_tuple, unsigned>::type,
                            std::tuple<unsigned, int, char, bool>>));
  BOOST_MPL_ASSERT((is_same<push_back<some_tuple, unsigned>::type,
                            std::tuple<int, char, bool, unsigned>>));
  BOOST_MPL_ASSERT_RELATION(empty<some_tuple>::type::value, ==, false);
  BOOST_MPL_ASSERT((is_same<at_c<some_tuple, 0>::type,
                            int>));
  BOOST_MPL_ASSERT((is_same<at_c<some_tuple, 1>::type,
                            char>));
  BOOST_MPL_ASSERT((is_same<back<some_tuple>::type,
                            bool>));
  BOOST_MPL_ASSERT((is_same<clear<some_tuple>::type,
                            std::tuple<>>));
  BOOST_MPL_ASSERT((is_same<pop_back<some_tuple>::type,
                            std::tuple<int, char>>));
  BOOST_MPL_ASSERT((contains<some_tuple, int>));
  BOOST_MPL_ASSERT((contains<some_tuple, char>));
  BOOST_MPL_ASSERT((contains<some_tuple, bool>));
  BOOST_MPL_ASSERT_NOT((contains<some_tuple, unsigned>));
ABL_RESTORE_WARNINGS
}

} // namespace meta
} // namespace atria
