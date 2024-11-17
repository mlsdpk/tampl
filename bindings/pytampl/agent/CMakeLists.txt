set(SRC_FILES bindings.cpp)

pybind11_add_module(agent ${SRC_FILES})
target_link_libraries(agent PRIVATE tampl pybind11::module)
target_include_directories(
  agent
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

install(TARGETS agent DESTINATION pytampl/agent)
