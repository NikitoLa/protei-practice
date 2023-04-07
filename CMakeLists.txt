cmake_minimum_required(VERSION 3.0)
project(Practice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT PKG_CONFIG_FOUND)
    include(CMakeFindDependencyMacro)
    find_dependency(PkgConfig)
endif ()

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/google/googletest
        GIT_TAG main)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/benchmark
        GIT_TAG main)
FetchContent_MakeAvailable(benchmark)

FetchContent_Declare(re2
        GIT_REPOSITORY https://github.com/google/re2.git
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/re2
        GIT_TAG main)
FetchContent_MakeAvailable(re2)

file(GLOB SRC
        "Source/*.h"
        "Source/*.cpp"
        )
include_directories(Source)

add_executable(Practice ${SRC})

target_link_libraries(Practice
        PRIVATE benchmark::benchmark)

target_link_libraries(Practice PRIVATE re2::re2)