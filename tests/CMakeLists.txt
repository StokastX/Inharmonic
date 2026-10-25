include(FetchContent)
# doctest's own CMakeLists.txt predates CMake 4, so only its sources are
# fetched (SOURCE_SUBDIR points nowhere) and the header target is made here.
FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        v2.5.3
    GIT_SHALLOW    TRUE
    SOURCE_SUBDIR  none)
FetchContent_MakeAvailable(doctest)

add_library(doctest INTERFACE)
target_include_directories(doctest SYSTEM INTERFACE ${doctest_SOURCE_DIR})
# Recent MSVC standard libraries reject doctest's own forward declarations of std types.
target_compile_definitions(doctest INTERFACE DOCTEST_CONFIG_USE_STD_HEADERS)

add_executable(inh_tests
    main.cpp
    test_version.cpp)
target_link_libraries(inh_tests PRIVATE
    inh::inh
    doctest)
target_compile_options(inh_tests PRIVATE ${INH_COMPILE_OPTIONS})

# One CTest entry per doctest TEST_CASE.
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(inh_tests)
