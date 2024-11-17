find_package(Eigen3 REQUIRED)
# create tampl as an empty lib for now
add_library(${PROJECT_NAME} SHARED)

# include all sub directories
add_subdirectory(agent)
add_subdirectory(core)
add_subdirectory(environment)
add_subdirectory(planner)

set(SRC_FILES tampl.cpp ${_agent_src_files} ${_core_src_files} ${_environment_src_files}
              ${_planner_src_files})

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
target_link_libraries(${PROJECT_NAME} PRIVATE ompl)

set_target_properties(
  ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${TAMPL_VERSION}"
                             POSITION_INDEPENDENT_CODE ON)

install(
  TARGETS ${PROJECT_NAME}
  # EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION ${TAMPL_RUNTIME_INSTALL_DIR}
  LIBRARY DESTINATION ${TAMPL_LIBRARY_INSTALL_DIR}
  ARCHIVE DESTINATION ${TAMPL_ARCHIVE_INSTALL_DIR}
  FRAMEWORK DESTINATION ${TAMPL_FRAMEWORK_INSTALL_DIR}
  PUBLIC_HEADER DESTINATION ${TAMPL_INCLUDE_INSTALL_DIR}/${PROJECT_NAME})

# Write/install version file
include(CMakePackageConfigHelpers)
set(VERSION_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake")
write_basic_package_version_file(
  ${VERSION_FILE}
  VERSION ${TAMPL_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(FILES ${VERSION_FILE} DESTINATION ${TAMPL_CMAKE_CONFIG_INSTALL_DIR})
