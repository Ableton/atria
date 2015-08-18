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

#include <atria/meta/concept.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace meta {

/*!
 * This is a example concept kinda compatible with C++1y concepts
 * lite. The problem with this mechanism is that it rises compilation
 * errors when the concept is not met, making it non suitable for
 * SFINAE-friendly concepts.
 */
template <typename T>
ABL_CONCEPT bool Example_concept()
{
  using namespace std;

  return valid<decltype(
    expressions(
      // Dereferenceable
      *declval<T>(),
      // Has value type
      declval<estd::Value_type<T>>(),
      // Can forward dereferenced to value type
      forward<estd::Value_type<T>>( *declval<T>() ),
      // Has an action() method that may return void
      (declval<T>().action(), can_be_void)
      ))>();
}

/*!
 * Models the concept:
 *   Example_concept
 */
struct example_model
{
  typedef int value_type;
  int operator*() { return 0; }
  void action() {}
};

/*!
 * Example non-model, missing action
 */
struct example_non_model
{
  typedef int value_type;
  std::string operator*() { return 0; }
  void action() {}
};

TEST(simple_concept, can_be_evaluated_like_aconcept_lite)
{
  EXPECT_TRUE(Example_concept<example_model>());
  // This is expected to fail to compile
  //   EXPECT_FALSE(Example_concept<ExampleNonModel>());
}

TEST(simple_concept, can_be_used_with_concept_assert)
{
  ABL_ASSERT_CONCEPT(Example_concept, example_model);
  // This is expected to fail to compile
  //   ABL_ASSERT_CONCEPT(Example_concept, ExampleNonModel);
}

/*!
 * Same concept as `Example_concept`, but modeled in a SFINAE-friendly
 * way, which is preferred.  This syntax has the advantage that
 * `declval` is required less in the specification.  On the other
 * hand, it is a bit more "magical"
 */
ABL_CONCEPT_SPEC(Example_concept_two)
{
  template <typename T>
  auto requires_(T&& x) -> decltype(
    expressions(
      // Dereferenceable
      *x,
      // Has value type
      std::declval<estd::Value_type<T>>(),
      // Can forward dereferenced to value type
      std::forward<estd::Value_type<T>>( *x ),
      // Has an action() method that may return void
      (x.action(), can_be_void)
      ));
};

TEST(concept, can_be_evaluated_like_aconcept_lite)
{
  EXPECT_TRUE(Example_concept_two<example_model>());
  EXPECT_FALSE(Example_concept_two<example_non_model>());
}

TEST(concept, can_be_used_with_concept_assert)
{
  ABL_ASSERT_CONCEPT(Example_concept_two, example_model);
  ABL_ASSERT_NOT_CONCEPT(Example_concept_two, example_non_model);
}

TEST(concept, can_use_models_with_concept_spec)
{
  EXPECT_TRUE(models<Example_concept_two_spec(example_model)>());
  EXPECT_FALSE(models<Example_concept_two_spec(example_non_model)>());
}

TEST(concept, can_use_check_with_concept_spec)
{
  EXPECT_TRUE(check<Example_concept_two_spec(example_model)>());
  // This should fail to compiler, rising an error in the line of
  // the specification that is not met.
  //   EXPECT_FALSE(check<Example_concept_two<void>(ExampleNonModel)>());
}

/*!
 * Finally, an example of specifying a SFINAE-friendly concept in two
 * steps, which migth seem clearer to some.
 */
struct Example_concept_spec
{
  template <typename T>
  auto requires_(T&& x) -> decltype(
    expressions(
      // Dereferenceable
      *x,
      // Has value type
      std::declval<estd::Value_type<T>>(),
      // Can forward dereferenced to value type
      std::forward<estd::Value_type<T>>( *x ),
      // Has an action() method that may return void
      (x.action(), can_be_void)
      ));
};

template <typename T>
ABL_CONCEPT bool Example_concept_three()
{
  return models<Example_concept_spec(T)>();
}

TEST(concept, can_be_defined_in_two_steps)
{
  EXPECT_TRUE(Example_concept_three<example_model>());
  EXPECT_FALSE(Example_concept_three<example_non_model>());
}

ABL_CONCEPT_SPEC(adl_swapable)
{
  template <typename T, typename U>
  auto requires_(T&& x, U&& y) -> decltype(
    expressions(
      (swap(x, y), can_be_void),
      (swap(y, x), can_be_void)));

  template <typename T>
  auto requires_(T&& x) -> decltype(
    requires_(x, x));
};

void swap(example_model&, example_model&);
void swap(example_model&, int&);
void swap(int&, example_model&);

TEST(concept, optional_multiple_arguments)
{
  EXPECT_TRUE((adl_swapable<example_model>()));
  EXPECT_TRUE((adl_swapable<example_model, int>()));
  EXPECT_FALSE((adl_swapable<example_model, float>()));
}

} // namespace meta
} // namespace atria
