set(SRC_FILES pddl.cpp)

pybind11_add_module(pddl ${SRC_FILES})
target_link_libraries(pddl PRIVATE tampl pybind11::module)
target_include_directories(
  pddl
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

install(TARGETS pddl DESTINATION pytampl/pddl)
