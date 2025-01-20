macro(_tampl_add_example name src_file)
    add_executable(tampl_example_${name} ${src_file}.cpp)
    target_link_libraries(tampl_example_${name} PUBLIC tampl)
endmacro()

# _tampl_add_example(test_task_planning test_task_planning)
# _tampl_add_example(decoupled_tamp decoupled_tamp)
# _tampl_add_example(pygame_tamp_discrete tamp/pygame_tamp_discrete)

# add_custom_target(copy_behavior_trees ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_CURRENT_SOURCE_DIR}/behavior_trees
#     ${CMAKE_BINARY_DIR}/examples/behavior_trees
#     COMMENT "Copying behavior trees..."
# )

# install(
#   TARGETS tampl_example_pygame_tamp_discrete
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
