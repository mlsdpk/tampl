function(tampl_add_python_module module_name src_files)
  pybind11_add_module(${module_name} ${src_files})
  target_link_libraries(${module_name} PRIVATE tampl pybind11::module)
  target_include_directories(
    ${module_name}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
           $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

  set_target_properties(${module_name} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

  if(UNIX AND NOT APPLE)
    set_target_properties(${module_name} PROPERTIES INSTALL_RPATH
                                                    "$ORIGIN/../lib")
  elseif(APPLE)
    set_target_properties(${module_name} PROPERTIES INSTALL_RPATH
                                                    "@loader_path/../lib")
  endif()

  set_target_properties(${module_name} PROPERTIES INSTALL_RPATH_USE_LINK_PATH
                                                  TRUE)

  install(TARGETS ${module_name} DESTINATION ${module_name})
endfunction()
