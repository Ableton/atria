// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/meta/concept.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace meta {

//!
// This is a example concept kinda compatible with C++1y concepts
// lite. The problem with this mechanism is that it rises compilation
// errors when the concept is not met, making it non suitable for
// SFINAE-friendly concepts.
//
template <typename T>
constexpr bool Example_concept()
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

//!
// Models the concept:
//   Example_concept
//
struct example_model
{
  typedef int value_type;
  int operator*() { return 0; }
  void action() {}
};

//!
// Example non-model, missing action
//
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

//!
// Same concept as `Example_concept`, but modeled in a SFINAE-friendly
// way, which is preferred.  This syntax has the advantage that
// `declval` is required less in the specification.  On the other
// hand, it is a bit more "magical"
//
template <typename _>
struct Example_concept_two : concept<Example_concept_two<_>>
{
  template <typename T>
  auto requires(T&& x) -> decltype(
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

TEST(concept, can_use_satisfies_with_concept_spec)
{
  EXPECT_TRUE(satisfies<Example_concept_two<void>(example_model)>());
  EXPECT_FALSE(satisfies<Example_concept_two<void>(example_non_model)>());
}

TEST(concept, can_use_check_with_concept_spec)
{
  EXPECT_TRUE(check<Example_concept_two<void>(example_model)>());
  // This should fail to compiler, rising an error in the line of
  // the specification that is not met.
  //   EXPECT_FALSE(check<Example_concept_two<void>(ExampleNonModel)>());
}

//!
// Finally, an example of specifying a SFINAE-friendly concept in two
// steps, which migth seem clearer to some.
//
struct Example_concept_spec
{
  template <typename T>
  auto requires(T&& x) -> decltype(
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
using Example_concept_three = concept<Example_concept_spec(T)>;

TEST(concept, can_be_defined_in_two_steps)
{
  EXPECT_TRUE(Example_concept_three<example_model>());
  EXPECT_FALSE(Example_concept_three<example_non_model>());
}

template <typename Arg1, typename Arg2=Arg1>
struct adl_swapable : concept<adl_swapable<Arg1, Arg2>>
{
  template <typename T, typename U>
  auto requires(T&& x, U&& y) -> decltype(
    expressions(
      (swap(x, y), can_be_void),
      (swap(y, x), can_be_void)));
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
