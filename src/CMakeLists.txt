set(TAMPL_TARGET_NAME "tampl")

include(GNUInstallDirs)
set(TAMPL_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/tampl")
set(TAMPL_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/tampl")
set(TAMPL_TARGETS_EXPORT_NAME "tampl-targets")
set(TAMPL_CMAKE_CONFIG_TEMPLATE
    "${PROJECT_SOURCE_DIR}/cmake/tampl-config.cmake.in")
set(TAMPL_CMAKE_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(TAMPL_CMAKE_VERSION_CONFIG_FILE
    "${TAMPL_CMAKE_CONFIG_DIR}/tampl-config-version.cmake")
set(TAMPL_CMAKE_PROJECT_CONFIG_FILE
    "${TAMPL_CMAKE_CONFIG_DIR}/tampl-config.cmake")

# RPATH stuff see https://cmake.org/Wiki/CMake_RPATH_handling
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(_rpath_portable_origin "@loader_path")
else()
  set(_rpath_portable_origin $ORIGIN)
endif()

# Use separate rpaths during build and install phases
set(CMAKE_SKIP_BUILD_RPATH TRUE)
# Don't use the install-rpath during the build phase
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${_rpath_portable_origin}")

# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# create tampl as an empty lib for now
add_library(${PROJECT_NAME} SHARED)

# include all sub directories
add_subdirectory(agent)
add_subdirectory(bt)
add_subdirectory(core)
add_subdirectory(environment)
add_subdirectory(planner)

set(SRC_FILES tampl.cpp ${_agent_src_files} ${_bt_src_files} ${_core_src_files}
              ${_environment_src_files} ${_planner_src_files})

target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/bt/gen> # for
                                                      # bt/gen/plugins_list.hpp
    $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    ompl::ompl
    behaviortree_cpp
    yaml-cpp)

if(TAMPL_BUILD_PYBINDINGS)
  target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
      $<BUILD_INTERFACE:${PYBIND11_INCLUDE_DIR}>
      $<BUILD_INTERFACE:${Python3_INCLUDE_DIRS}>)

  target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
      ${pybind11_LIBRARIES}
      pybind11::module
      pybind11::pybind11
      pybind11::embed
      ${Python3_LIBRARIES})
endif()

set_target_properties(
  ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${TAMPL_VERSION}"
                             POSITION_INDEPENDENT_CODE ON)

# Make sure OS X does not have any issues with missing symbols
if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-undefined dynamic_lookup")
endif(APPLE)

# INSTALL

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${TAMPL_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${TAMPL_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMinorVersion
  DEPENDENCIES "ompl 1.6.0;behaviortree_cpp 4.6.2"
)
