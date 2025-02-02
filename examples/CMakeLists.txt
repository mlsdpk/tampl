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
        share/${PROJECT_NAME}/
    FILES_MATCHING PATTERN "*.pddl" PATTERN "*.md")
