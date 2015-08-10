# Copyright (c) 2014, 2015 Ableton AG, Berlin

cmake_minimum_required(VERSION 2.8.12)

project(Atria C CXX)
set(Atria_VERSION_MAJOR 0)
set(Atria_VERSION_MINOR 0)

# Enable C++11
include(CheckCXXCompilerFlag)
if(WIN32)
  # Check if we are using Visual Studio 2013 or later
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(FATAL_ERROR
      "You are using an unsupported Windows compiler! "
      "(Visual C++ 2013 or later required)")
  endif()
else()
  set(cxx11_options -std=c++11)
  CHECK_CXX_COMPILER_FLAG(${cxx11_options} COMPILER_SUPPORTS_CXX11)

  if(NOT COMPILER_SUPPORTS_CXX11)
    message(FATAL_ERROR
      "The compiler ${CMAKE_CXX_COMPILER} has insufficient C++11 support. "
      "Please use a different C++ compiler.")
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
    -Wno-weak-vtables)
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
find_package(Boost 1.54 COMPONENTS program_options REQUIRED)

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
  ${Boost_INCLUDE_DIRS})
target_compile_options(atria
  PUBLIC ${cxx11_options} ${warning_options})
target_link_libraries(atria
  ${Boost_LIBRARIES})

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
    ${CMAKE_THREAD_LIBS_INIT})
  add_test(atria-test-all atria-test-all)

  add_executable(atria-benchmark-xform
    src/atria/xform/benchmark_main.cpp)
  target_link_libraries(atria-benchmark-xform
    atria)
  add_test(atria-benchmark-xform atria-benchmark-xform)
endif()
