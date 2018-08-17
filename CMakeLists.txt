cmake_minimum_required(VERSION 3.0.2)

project(CuttleLang VERSION 0.1 LANGUAGES CXX)

include(CMakeToolsHelpers OPTIONAL)

file(GLOB SRCS "src/*.cpp")
file(GLOB_RECURSE TEST_SRCS "tests/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.hpp")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -Wextra")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif()

if(NOT TARGET cuttle_parser)
    add_subdirectory(deps/cuttle-parser)
endif()

if(NOT TARGET cuttle_translator)
    add_subdirectory(deps/cuttle-translator)
endif()

if(NOT TARGET cuttle_generator)
    add_subdirectory(deps/cuttle-generator)
endif()

set(DEPS_INCLUDE_DIRS
    "deps/cuttle-parser/src"
    "deps/cuttle-translator/src"
    "deps/cuttle-generator/src")

add_library(cuttle_lang SHARED ${SRCS} ${HEADERS})
add_executable(cuttle_lang_tests ${TEST_SRCS} ${HEADERS} ${TEST_HEADERS} tests/cuttle-test/src/measure.hpp)

target_include_directories(cuttle_lang PRIVATE "src/" ${DEPS_INCLUDE_DIRS})
target_include_directories(cuttle_lang_tests PRIVATE "src/" ${DEPS_INCLUDE_DIRS} "tests/" "tests/cuttle-test/src/")

target_link_libraries(cuttle_lang cuttle_parser)
target_link_libraries(cuttle_lang cuttle_generator)
target_link_libraries(cuttle_lang cuttle_translator)

target_link_libraries(cuttle_lang_tests cuttle_lang)
