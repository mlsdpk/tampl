set(plugin_libs "")

function(tampl_add_bt_plugin plugin_name src_files)
  add_library(${plugin_name} SHARED ${src_files})

  target_include_directories(
    ${plugin_name} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
                          $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

  target_compile_definitions(${plugin_name} PRIVATE BT_PLUGIN_EXPORT)
  target_link_libraries(${plugin_name} tampl behaviortree_cpp)
  add_dependencies(${plugin_name} tampl)

  set_target_properties(${plugin_name} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

  if(UNIX AND NOT APPLE)
    set_target_properties(${plugin_name} PROPERTIES INSTALL_RPATH
                                                    "$ORIGIN/../lib")
  elseif(APPLE)
    set_target_properties(${plugin_name} PROPERTIES INSTALL_RPATH
                                                    "@loader_path/../lib")
  endif()

  set_target_properties(${plugin_name} PROPERTIES INSTALL_RPATH_USE_LINK_PATH
                                                  TRUE)

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

tampl_add_bt_plugin(
  bt_pddl_planner ${CMAKE_CURRENT_SOURCE_DIR}/plugins/planner/pddl_planner.cpp)

# we will embed the list of plugin names inside a header file
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
configure_file(plugins/plugins_list.hpp.in ${GENERATED_DIR}/plugins_list.hpp)

add_library(planner_bt_engine SHARED planner_bt_engine.cpp)
target_include_directories(
  planner_bt_engine
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_link_libraries(planner_bt_engine behaviortree_cpp)

set_target_properties(planner_bt_engine PROPERTIES BUILD_WITH_INSTALL_RPATH
                                                   TRUE)

if(UNIX AND NOT APPLE)
  set_target_properties(planner_bt_engine PROPERTIES INSTALL_RPATH
                                                     "$ORIGIN/../lib")
elseif(APPLE)
  set_target_properties(planner_bt_engine PROPERTIES INSTALL_RPATH
                                                     "@loader_path/../lib")
endif()

set_target_properties(planner_bt_engine PROPERTIES INSTALL_RPATH_USE_LINK_PATH
                                                   TRUE)
