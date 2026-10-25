# The nanobind extension inharmonic._core. It is written next to the Python
# sources (python/inharmonic/) so the editable install picks it up directly.
# Default to the repo's virtual environment (created by scripts/setup_venv.py).
if(NOT DEFINED Python_EXECUTABLE)
    if(WIN32)
        set(venv_python "${PROJECT_SOURCE_DIR}/.venv/Scripts/python.exe")
    else()
        set(venv_python "${PROJECT_SOURCE_DIR}/.venv/bin/python")
    endif()
    if(EXISTS "${venv_python}")
        set(Python_EXECUTABLE "${venv_python}")
    endif()
endif()

find_package(Python 3.10 REQUIRED COMPONENTS Interpreter Development.Module)

execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE nanobind_ROOT
    RESULT_VARIABLE nanobind_found)
if(NOT nanobind_found EQUAL 0)
    message(FATAL_ERROR "nanobind not found in ${Python_EXECUTABLE}: run scripts/setup_venv.py")
endif()
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(_core src/module.cpp)
target_link_libraries(_core PRIVATE inh::inh)

# $<1:...> stops multi-config generators from appending a per-config folder.
set_target_properties(_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_SOURCE_DIR}/inharmonic>)
