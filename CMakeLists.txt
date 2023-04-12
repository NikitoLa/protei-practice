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

FetchContent_Declare(boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/boost
        )
FetchContent_MakeAvailable(boost)

FetchContent_Declare(pcre
        URL https://github.com/PCRE2Project/pcre2/releases/download/pcre2-10.42/pcre2-10.42.tar.gz
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/pcre
        )
FetchContent_MakeAvailable(pcre)

file(GLOB SRC
        "Source/*.h"
        "Source/*.cpp"
        )
include_directories(Source)

add_executable(Practice ${SRC})

target_link_libraries(Practice
        PRIVATE benchmark::benchmark)

target_link_libraries(Practice PRIVATE re2::re2)

# set( BOOST_ROOT "/home/nikitola/Downloads/boost_1_81_0/lib/" CACHE PATH "Boost library path" )
# set( Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )

# find_package(Boost REQUIRED regex)
# include_directories(${BOOST_INCLUDE_DIRS})

# target_link_libraries(Practice PRIVATE
#         ${Boost_LIBRARIES}
# )

set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/boost)
set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)
find_package(Boost REQUIRED regex)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

target_link_libraries( Practice PRIVATE ${Boost_LIBRARIES} )



