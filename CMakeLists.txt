# Copyright (c) 2014 Ableton AG, Berlin

cmake_minimum_required(VERSION 2.8.12)

project(Atria C CXX)
set(Atria_VERSION_MAJOR 0)
set(Atria_VERSION_MINOR 0)

# Enable C++11
include(CheckCXXCompilerFlag)
if(WIN32)
  # Check if we are using Visual Studio 2013 or later
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(FATAL_ERROR "You are using an unsupported Windows compiler! (Visual C++ 2013 or later required)")
  endif()
else()
  set(cxx11_options -std=c++11)
  CHECK_CXX_COMPILER_FLAG(${cxx11_options} COMPILER_SUPPORTS_CXX11)

  if(NOT COMPILER_SUPPORTS_CXX11)
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has insufficient C++11 support. Please use a different C++ compiler.")
  endif()
endif()

# Build debug by default
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Enable warnings
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang
    OR CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
  set(warning_options
    #-Werror
    #-Weverything
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-documentation-unknown-command
    -Wno-exit-time-destructors
    -Wno-padded
    -Wno-undefined-reinterpret-cast
  )
elseif(MSVC)
  set(warning_options /WX /W4 /wd4503 /wd4512)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
set(CMAKE_MACOSX_RPATH ON)

enable_testing()

if(DEFINED Boost_INCLUDE_DIR)
  get_filename_component(Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR} ABSOLUTE)
endif()
find_package(Boost 1.54 REQUIRED)

set(GTEST_SOURCE
  "${CMAKE_CURRENT_SOURCE_DIR}/../googletest"
  CACHE FILEPATH "googletest source directory")
set(GTEST_FOUND FALSE)
if(EXISTS "${GTEST_SOURCE}" AND IS_DIRECTORY "${GTEST_SOURCE}")
  get_filename_component(GTEST_SOURCE ${GTEST_SOURCE} ABSOLUTE)
  set(GTEST_FOUND TRUE)
  find_package(Threads REQUIRED)
endif()

include(FeatureSummary)
add_feature_info(GoogleTest ${GTEST_FOUND} "used for unit testing.")
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

# Defining Atria
add_library(AtriaLib
  src/atria/estd/memory.hpp
  src/atria/estd/type_traits.hpp
  src/atria/estd/utility.hpp
  src/atria/funken/commit.hpp
  src/atria/funken/concepts.hpp
  src/atria/funken/detail
  src/atria/funken/detail/access.hpp
  src/atria/funken/detail/no_value.hpp
  src/atria/funken/detail/root_signals.hpp
  src/atria/funken/detail/signals.hpp
  src/atria/funken/detail/watchable.hpp
  src/atria/funken/detail/xform_signals.hpp
  src/atria/funken/in.hpp
  src/atria/funken/inout.hpp
  src/atria/funken/out.hpp
  src/atria/funken/sensor.hpp
  src/atria/funken/state.hpp
  src/atria/funken/structure.hpp
  src/atria/funken/watch.hpp
  src/atria/funken/xformed.hpp
  src/atria/meta/common_type.hpp
  src/atria/meta/pack.hpp
  src/atria/meta/std_tuple.hpp
  src/atria/meta/utils.hpp
  src/atria/testing/benchmark.hpp
  src/atria/testing/spies.hpp
  src/atria/variant/match.hpp
  src/atria/variant/visitor.hpp
  src/atria/xform/any_state.hpp
  src/atria/xform/functional.hpp
  src/atria/xform/reduce.hpp
  src/atria/xform/reducers.hpp
  src/atria/xform/state.hpp
  src/atria/xform/transduce.hpp
  src/atria/xform/transducer.hpp
  src/atria/xform/transducers.hpp
  src/atria/testing/benchmark.cpp
  )
set_target_properties(AtriaLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(AtriaLib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/compat>
  ${Boost_INCLUDE_DIRS})
target_compile_options(AtriaLib
  PUBLIC ${cxx11_options} ${warning_options})
target_link_libraries(AtriaLib)

# Definining tests
if(GTEST_FOUND)
  add_library(gtest_internal STATIC
    ${GTEST_SOURCE}/src/gtest-all.cc
    ${GTEST_SOURCE}/src/gtest_main.cc
    )
  target_include_directories(gtest_internal PUBLIC
    ${GTEST_SOURCE} ${GTEST_SOURCE}/include)
  target_compile_options(gtest_internal PUBLIC
    ${cxx11_options} -Wno-global-constructors)

  add_executable(AtriaTest
    src/atria/funken/tst_in_and_out.cpp
    src/atria/funken/tst_sensor.cpp
    src/atria/funken/tst_state.cpp
    src/atria/funken/tst_structure.cpp
    src/atria/funken/tst_xformed.cpp
    src/atria/meta/tst_concepts.cpp
    src/atria/meta/tst_pack.cpp
    src/atria/meta/tst_std_tuple.cpp
    src/atria/testing/tst_spies.cpp
    src/atria/variant/tst_match.cpp
    src/atria/xform/tst_transducers.cpp
    src/atria/xform/tst_transducers_benchmark.cpp
    )

  target_link_libraries(AtriaTest
    AtriaLib
    gtest_internal
    ${CMAKE_THREAD_LIBS_INIT})

  add_test(AtriaTestCase AtriaTest)
endif()
