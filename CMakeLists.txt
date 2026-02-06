cmake_minimum_required(VERSION 3.16)

project(DKVApp
    VERSION 0.1
    DESCRIPTION "Distributed Key-Value Store App (educational project)"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(tests)

# src paths
file(GLOB_RECURSE SOURCES "src/*.cpp")

set(LIB_SOURCES ${SOURCES})

list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")

add_library(dkv_server_core STATIC ${LIB_SOURCES})

# create executable file
add_executable(dkv_server src/main.cpp)

target_link_libraries(dkv_server PRIVATE dkv_server_core)

# Include directories
target_include_directories(dkv_server_core PUBLIC
    src
    ${CMAKE_SOURCE_DIR}
)

target_include_directories(dkv_server PUBLIC
    src
    ${CMAKE_SOURCE_DIR}
)

if (MSVC)
    target_compile_options(dkv_server PRIVATE /W4)
else()
    target_compile_options(dkv_server PRIVATE -Wall -Wextra -Wpedantic)
endif()