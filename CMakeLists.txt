cmake_minimum_required(VERSION 3.19)
project(tampl)

set(TAMPL_VERSION_MAJOR
    0
    CACHE STRING "major version of TAMPL" FORCE)
set(TAMPL_VERSION_MINOR
    1
    CACHE STRING "minor version of TAMPL" FORCE)
set(TAMPL_VERSION_PATCH
    0
    CACHE STRING "patch version of TAMPL" FORCE)
set(TAMPL_VERSION
    "${TAMPL_VERSION_MAJOR}.${TAMPL_VERSION_MINOR}.${TAMPL_VERSION_PATCH}"
    CACHE STRING "version of TAMPL" FORCE)

option(TAMPL_BUILD_PYBINDINGS "Build python bindings." OFF)
option(TAMPL_BUILD_EXAMPLES "Build example applications." ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmake/utils.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add dependencies
include(cmake/dependencies.cmake)

add_subdirectory(src)

if(TAMPL_BUILD_PYBINDINGS)
  message(STATUS "Building python bindings...")
  add_subdirectory(bindings)
endif()

if(TAMPL_BUILD_EXAMPLES)
  message(STATUS "Building example applications...")
  add_subdirectory(examples)
endif()
