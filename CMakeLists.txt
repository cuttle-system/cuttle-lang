cmake_minimum_required(VERSION 3.0.2)
project(CuttleLang VERSION 0.2 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CMakeToolsHelpers OPTIONAL)
include(add_dependency)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
  set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} -Wextra -O3")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif()

set(SRC_INCLUDE_DIRECTORIES
    "src/"
    "../cuttle-parser/src"
    "../cuttle-translator/src"
    "../cuttle-generator/src")

file(GLOB SRCS "src/*.cpp")
file(GLOB_RECURSE TEST_SRCS "tests/*.cpp")
file(GLOB CUTTLE_TEST_SRCS "../cuttle-test/src/*.cpp")

file(GLOB HEADERS "src/*.hpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.hpp")

add_dependency(cuttle-parser)
add_dependency(cuttle-translator)
add_dependency(cuttle-generator)

add_library(cuttle-lang SHARED ${SRCS} ${HEADERS})
add_executable(cuttle-lang-tests ${CUTTLE_TEST_SRCS} ${TEST_SRCS} ${HEADERS} ${TEST_HEADERS})

target_include_directories(cuttle-lang PRIVATE ${SRC_INCLUDE_DIRECTORIES})
target_include_directories(cuttle-lang-tests
    PRIVATE
    "tests/"
    "../cuttle-test/src/"
    ${SRC_INCLUDE_DIRECTORIES})

target_link_libraries(cuttle-lang
    cuttle-parser
    cuttle-generator
    cuttle-translator)

target_link_libraries(cuttle-lang-tests cuttle-lang)
