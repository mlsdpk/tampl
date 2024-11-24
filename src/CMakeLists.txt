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

find_package(Eigen3 REQUIRED)
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
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${Boost_INCLUDE_DIR}")

# ompl related
set(OMPL_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/thirdparty/ompl/src")
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${OMPL_INCLUDE_DIRS}>
         # for ompl/config.h
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/thirdparty/ompl/src>)

# BT related
set(BTV4_INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/thirdparty/BehaviorTree.CPP/include")
target_include_directories(${PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${BTV4_INCLUDE_DIRS}>)

target_link_libraries(${PROJECT_NAME} PUBLIC planner_bt_engine ompl
                                             behaviortree_cpp)

set_target_properties(
  ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${TAMPL_VERSION}"
                             POSITION_INDEPENDENT_CODE ON)

# INSTALL

# Write/install version file
include(CMakePackageConfigHelpers)
set(VERSION_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake")
configure_package_config_file(
  ${TAMPL_CMAKE_CONFIG_TEMPLATE} ${TAMPL_CMAKE_PROJECT_CONFIG_FILE}
  INSTALL_DESTINATION ${TAMPL_CONFIG_INSTALL_DIR}
  NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
  ${TAMPL_CMAKE_VERSION_CONFIG_FILE}
  VERSION ${TAMPL_VERSION}
  COMPATIBILITY SameMinorVersion)

install(FILES ${TAMPL_CMAKE_PROJECT_CONFIG_FILE}
              ${TAMPL_CMAKE_VERSION_CONFIG_FILE}
        DESTINATION ${TAMPL_CONFIG_INSTALL_DIR})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES INSTALL_RPATH
             "${CMAKE_INSTALL_RPATH}:${_rpath_portable_origin}/../lib")

install(
  TARGETS ${PROJECT_NAME} planner_bt_engine ompl
  EXPORT ${TAMPL_TARGETS_EXPORT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  PUBLIC_HEADER DESTINATION ${TAMPL_INCLUDE_INSTALL_DIR})

install(
  EXPORT ${TAMPL_TARGETS_EXPORT_NAME}
  FILE ${TAMPL_PROJECT_TARGETS_FILE}
  NAMESPACE TAMPL::
  DESTINATION ${TAMPL_CONFIG_INSTALL_DIR}
  COMPONENT ${TAMPL_TARGET_NAME}_Development)
