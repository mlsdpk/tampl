# configure default BT plugins

set(plugin_libs "")

function(tampl_add_bt_plugin plugin_name src_files)
  add_library(${plugin_name} SHARED ${src_files})

  target_include_directories(
    ${plugin_name} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
                          $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

  target_compile_definitions(${plugin_name} PRIVATE BT_PLUGIN_EXPORT)
  target_link_libraries(${plugin_name} tampl behaviortree_cpp)
  add_dependencies(${plugin_name} tampl)

  install(
    TARGETS ${plugin_name}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

  list(APPEND plugin_libs ${plugin_name})
  set(plugin_libs
      "${plugin_libs}"
      PARENT_SCOPE)
endfunction()

##################################
# register all the plugins below #
##################################

# actions
tampl_add_bt_plugin(bt_action_add_to_plan_skeleton ${CMAKE_CURRENT_SOURCE_DIR}/plugins/actions/add_to_plan_skeleton.cpp)

# decorators
tampl_add_bt_plugin(bt_decorator_loop_task_plan ${CMAKE_CURRENT_SOURCE_DIR}/plugins/decorators/loop_task_plan.cpp)

# planner
tampl_add_bt_plugin(bt_task_planner ${CMAKE_CURRENT_SOURCE_DIR}/plugins/planner/task_planner.cpp)

##################################
# register all the plugins above #
##################################

# we will embed the list of plugin names inside a header file
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
configure_file(plugins/plugins_list.hpp.in ${GENERATED_DIR}/plugins_list.hpp)

set(_bt_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/planner_bt_engine.cpp
    PARENT_SCOPE)

#########################################################################################

# configure default behavior tree xml files

set(BEHAVIOR_TREES_BUILD_DIR "${CMAKE_BINARY_DIR}/behavior_trees")
set(BEHAVIOR_TREES_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/behavior_trees")
configure_file(behavior_trees/config.hpp.in ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/bt/behavior_trees/config.hpp @ONLY)

add_custom_target(copy_behavior_trees ALL)
add_custom_command(TARGET copy_behavior_trees POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/behavior_trees
        ${CMAKE_BINARY_DIR}/behavior_trees
    COMMENT "Copying behavior trees into build directory")

install(
    FILES
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/bt/behavior_trees/config.hpp
    DESTINATION
        include/${PROJECT_NAME}-${TAMPL_VERSION}/${PROJECT_NAME}/bt/behavior_trees)

install(
    DIRECTORY
        ${PROJECT_SOURCE_DIR}/behavior_trees/
    DESTINATION
        share/${PROJECT_NAME}/behavior_trees
    FILES_MATCHING PATTERN "*.xml" PATTERN "*.md")
