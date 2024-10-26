set(SRC_FILES fast_forward_py.cpp)

pybind11_add_module(planner ${SRC_FILES})
target_link_libraries(planner PUBLIC tampl PRIVATE pybind11::module)
target_include_directories(
  planner
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

install(TARGETS planner DESTINATION pytampl/planner)
