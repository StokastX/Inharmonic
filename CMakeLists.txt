cmake_minimum_required(VERSION 3.25)

project(Inharmonic
    VERSION 0.1.0
    DESCRIPTION "Physically modelled piano"
    LANGUAGES CXX)

option(INHARMONIC_BUILD_TESTS  "Build the doctest unit tests"     ON)
option(INHARMONIC_BUILD_PYTHON "Build the nanobind Python module" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The Python module is a shared library that links the static library below.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Strict warnings for our own targets (fetched dependencies keep their own).
if(MSVC)
    set(INH_COMPILE_OPTIONS /W4 /permissive- /utf-8 /Zc:__cplusplus /Zc:preprocessor)
else()
    set(INH_COMPILE_OPTIONS -Wall -Wextra -Wpedantic -Wshadow)
endif()

# inh: the whole engine. The piano description is shared; the real-time modal
# solver (inh::modal) and the offline FD reference (inh::fd) both build on it
# and never on each other, so the reference stays independent of what it checks.
add_library(inh STATIC
    src/version.cpp)
add_library(inh::inh ALIAS inh)

target_include_directories(inh PUBLIC include)
target_compile_features(inh PUBLIC cxx_std_20)
target_compile_options(inh PRIVATE ${INH_COMPILE_OPTIONS})

if(INHARMONIC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(INHARMONIC_BUILD_PYTHON)
    add_subdirectory(python)
endif()
