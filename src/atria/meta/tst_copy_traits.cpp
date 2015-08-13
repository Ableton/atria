// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/meta/copy_traits.hpp>
#include <atria/testing/gtest.hpp>
#include <typeinfo>

namespace atria {
namespace meta {

TEST(copy_traits, copy_decay)
{
  static_assert(std::is_same<copy_decay_t<const float, int>,
                             const int>{}, "");
  static_assert(std::is_same<copy_decay_t<const float&, int>,
                             const int&>{}, "");
  static_assert(std::is_same<copy_decay_t<float, int>,
                             int>{}, "");
  static_assert(std::is_same<copy_decay_t<float&&, int>,
                             int&&>{}, "");
}

} // namespace meta
} // namespace atria
