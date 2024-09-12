# Set the directory paths for the FFPlanner
set(FF_PLANNER_DIR_BUILD "${CMAKE_BINARY_DIR}/ffplanner/src/ffplanner")
set(FF_PLANNER_EXECUTABLE_BUILD "${FF_PLANNER_DIR_BUILD}/ff")
set(FF_PLANNER_EXECUTABLE_INSTALL "${CMAKE_INSTALL_PREFIX}/bin/ffplanner")

if(APPLE)
  # Use the URL for macOS
  set(FF_URL "https://github.com/ronuchit/FF.git")
  set(FF_DOWNLOAD_COMMAND git clone ${FF_URL} ${FF_PLANNER_DIR_BUILD})
else()
  # Use the URL for Linux or other UNIX-like systems
  set(FF_URL "https://fai.cs.uni-saarland.de/hoffmann/ff/FF-v2.3.tgz")
  set(FF_DOWNLOAD_COMMAND "")
endif()

include(ExternalProject)

ExternalProject_Add(
  ffplanner
  PREFIX ${CMAKE_BINARY_DIR}/ffplanner
  DOWNLOAD_COMMAND ${FF_DOWNLOAD_COMMAND}
  URL ${FF_URL}
  DOWNLOAD_NO_EXTRACT 1
  CONFIGURE_COMMAND ""
  BUILD_IN_SOURCE 1
  BUILD_COMMAND make
  INSTALL_COMMAND
    ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ffplanner/src/ffplanner/ff
    ${FF_PLANNER_EXECUTABLE_INSTALL}
  LOG_DOWNLOAD ON
  LOG_BUILD ON)

# Ensure FFPlanner is built before tampl
add_dependencies(tampl ffplanner)

# Pass both build and install paths to the library
target_compile_definitions(
  tampl
  PRIVATE FF_PLANNER_EXECUTABLE_BUILD="${FF_PLANNER_EXECUTABLE_BUILD}"
          FF_PLANNER_EXECUTABLE_INSTALL="${FF_PLANNER_EXECUTABLE_INSTALL}")
