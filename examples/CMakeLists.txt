# Where to put all the LIBRARY target files when built.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# RPATH stuff see https://cmake.org/Wiki/CMake_RPATH_handling
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(_rpath_portable_origin "@loader_path")
else()
  set(_rpath_portable_origin $ORIGIN)
endif()

# rpath options for build

set(CMAKE_BUILD_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# rpath options for install

# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# FIXME: adding share here temporarily since ompl is installing under share not under lib for some reason
set(CMAKE_INSTALL_RPATH
    "${_rpath_portable_origin}/../../lib;${_rpath_portable_origin}/../../share")

################################################################################

macro(_tampl_add_example name src_file)
    add_executable(tampl_example_${name} ${src_file})
    target_link_libraries(tampl_example_${name} PUBLIC tampl)
    install(
        TARGETS tampl_example_${name}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/examples)
endmacro()

_tampl_add_example(task_01_simple_pddl_task_planning task/01_simple_pddl_task_planning.cpp)
_tampl_add_example(task_02_simple_pddl_task_planning_with_bt task/02_simple_pddl_task_planning_with_bt.cpp)


# handle data files

add_custom_target(copy_data_files ALL)
add_custom_command(TARGET copy_data_files POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/examples/data
        ${CMAKE_BINARY_DIR}/examples/data
    COMMENT "Copying data files into build directory")

install(
    DIRECTORY
        ${PROJECT_SOURCE_DIR}/examples/data
    DESTINATION
        ${CMAKE_INSTALL_BINDIR}/examples
    FILES_MATCHING PATTERN "*.pddl" PATTERN "*.md")
