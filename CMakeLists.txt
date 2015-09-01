# Copyright (c) 2014, 2015 Ableton AG, Berlin

cmake_minimum_required(VERSION 3.2.2)

project(Atria C CXX)
set(Atria_VERSION_MAJOR 0)
set(Atria_VERSION_MINOR 0)

# Enable C++11
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(CMAKE_CXX_STANDARD STREQUAL 14)
  add_definitions(-DABL_CXX14=1)
else()
  add_definitions(-DABL_CXX14=0)
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
    -Werror
    -Weverything
    -Wno-disabled-macro-expansion
    -Wno-string-conversion
    -Wno-global-constructors
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-documentation-unknown-command
    -Wno-exit-time-destructors
    -Wno-padded
    -Wno-undefined-reinterpret-cast
    -Wno-weak-vtables
    -Wno-undefined-internal)
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

set(COVERAGE 0 CACHE BOOL "Generate a coverage report (gcc only)")
set(USE_COVERAGE FALSE)
set(coverage_options "")
if (COVERAGE AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(USE_COVERAGE TRUE)
  set(coverage_options "-fprofile-arcs -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${coverage_options}")
endif()

include(FeatureSummary)
add_feature_info(Tests ${GTEST_FOUND}
  "requires Google Test sources (GTEST_SOURCE)")
add_feature_info(Coverage ${USE_COVERAGE}
  "code coverage with tests, requires GCC and COVERAGE=1.")
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE atria_sources "src/*.hpp" "src/*.cpp")
file(GLOB_RECURSE atria_test_sources "src/tst_*.cpp")
file(GLOB_RECURSE atria_main_sources "src/*_main.cpp")
list(REMOVE_ITEM  atria_sources ${atria_test_sources})
list(REMOVE_ITEM  atria_sources ${atria_main_sources})

# Defining Atria
add_library(atria ${atria_sources})
set_target_properties(atria PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(atria PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/compat>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/eggs-variant/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/cxxopts/src>
  ${Boost_INCLUDE_DIRS})
target_compile_options(atria
  PUBLIC
  ${warning_options})
target_link_libraries(atria
  ${Boost_LIBRARIES}
  ${coverage_options})

# Definining tests
if(GTEST_FOUND)
  add_library(gtest_internal STATIC
    ${GTEST_SOURCE}/src/gtest-all.cc
    ${GTEST_SOURCE}/src/gtest_main.cc)
  target_include_directories(gtest_internal PUBLIC
    ${GTEST_SOURCE} ${GTEST_SOURCE}/include)
  target_compile_options(gtest_internal PUBLIC
    ${cxx11_options} -Wno-global-constructors)

  add_executable(atria-test-all
    ${atria_test_sources})
  target_link_libraries(atria-test-all
    atria
    gtest_internal
    ${CMAKE_THREAD_LIBS_INIT}
    ${coverage_options})
  add_test(atria-test-all atria-test-all)

  add_executable(atria-benchmark-xform
    src/atria/xform/benchmark_main.cpp)
  target_link_libraries(atria-benchmark-xform
    atria
    ${coverage_options})
  add_test(atria-benchmark-xform atria-benchmark-xform)
endif()
