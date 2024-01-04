# Building
# Build cmake inside a build/ directory
# cmake -B build/
# To enable unit tests
# cmake -B build -DBUILD_TESTS=ON

cmake_minimum_required(VERSION 3.10)
project(Webserv)

set(CMAKE_CXX_STANDARD 98)

file(GLOB_RECURSE WEBSERV_SOURCES
    src/*.cpp
    src/config/*.cpp
    src/helpers/*.cpp
    src/http/*.cpp
    src/reactor/*.cpp
    src/stream/*.cpp
    src/utils/*.cpp
    src/os/*.cpp
    src/reactor/IEventHandler.hpp
)

add_executable(webserv ${WEBSERV_SOURCES})
target_compile_options(webserv PRIVATE -Wall)

# Unit Tests Section
option(BUILD_TESTS "Enable unit tests" OFF)
if(NOT BUILD_TESTS)
    return()
endif()

enable_testing()
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TEST_SOURCES test/*.cpp)
file(GLOB_RECURSE ALL_SOURCES src/*.cpp)
list(REMOVE_ITEM ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(unit_tests ${TEST_SOURCES} ${ALL_SOURCES})
target_link_libraries(unit_tests PRIVATE gtest pthread)
target_compile_options(unit_tests PRIVATE -Wall)

add_test(NAME unit_tests COMMAND unit_tests)
