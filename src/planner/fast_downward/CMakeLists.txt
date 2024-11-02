# set the directory paths for the FDPlanner
set(FD_PLANNER_SRC_DIR "${CMAKE_SOURCE_DIR}/thirdparty/downward")
set(FD_PLANNER_DIR_BUILD "${CMAKE_BINARY_DIR}/thirdparty/downward/")
set(FD_PLANNER_EXECUTABLE_BUILD "${FD_PLANNER_DIR_BUILD}/fast-downward.py")
set(FD_PLANNER_EXECUTABLE_INSTALL "${CMAKE_INSTALL_PREFIX}/bin/fdplanner")

# post build
add_custom_target(fd_planner_post_build ALL DEPENDS ${FD_PLANNER_SRC_DIR})
add_custom_command(
  TARGET fd_planner_post_build
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${FD_PLANNER_SRC_DIR}/driver
          ${FD_PLANNER_DIR_BUILD}/driver
  COMMAND ${CMAKE_COMMAND} -E copy ${FD_PLANNER_SRC_DIR}/fast-downward.py
          ${FD_PLANNER_EXECUTABLE_BUILD}
  COMMENT "Copying fast-downward planner scripts into output directory")

# Pass both build and install paths to the library
target_compile_definitions(
  tampl
  PRIVATE FD_PLANNER_EXECUTABLE_BUILD="${FD_PLANNER_EXECUTABLE_BUILD}"
          FD_PLANNER_EXECUTABLE_INSTALL="${FD_PLANNER_EXECUTABLE_INSTALL}")
