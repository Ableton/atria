// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/concepts.hpp>
#include <atria/xform/any_state.hpp>
#include <atria/xform/state_wrapper.hpp>

#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(state_traits, concept)
{
  meta::check<State_spec(int)>();
  meta::check<State_spec(state_wrapper<no_tag, int, int>)>();
  meta::check<State_spec(any_state)>();
}

} // namespace xform
} // namespace atria
