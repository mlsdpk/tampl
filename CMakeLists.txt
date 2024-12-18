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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmake/utils.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(ompl REQUIRED)
find_package(behaviortree_cpp REQUIRED)

add_subdirectory(src)

option(TAMPL_BUILD_PYBINDINGS "Build python bindings." ON)
if(TAMPL_BUILD_PYBINDINGS)
  message(STATUS "Building python bindings...")
  add_subdirectory(bindings)
endif()

option(TAMPL_BUILD_EXAMPLES "Build example applications." ON)
if(TAMPL_BUILD_EXAMPLES)
  message(STATUS "Building example applications...")
  add_subdirectory(examples)
endif()
