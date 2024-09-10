cmake_minimum_required(VERSION 3.15)
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

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# installation destinations
set(TAMPL_INCLUDE_INSTALL_DIR "include")
set(TAMPL_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}")
set(TAMPL_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
set(TAMPL_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
set(TAMPL_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
set(TAMPL_CMAKE_CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")

# subdirectories
add_subdirectory(src)
add_subdirectory(bindings)

option(TAMPL_BUILD_EXAMPLES "Build example applications." ON)
if(TAMPL_BUILD_EXAMPLES)
    message(STATUS "Building example applications.")
    add_subdirectory(examples)
endif()

install(
  EXPORT tamplTargets
  DESTINATION ${TAMPL_CMAKE_CONFIG_INSTALL_DIR}
  FILE tampl-config.cmake)
