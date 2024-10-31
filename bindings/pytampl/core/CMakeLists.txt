set(SRC_FILES bindings.cpp)

pybind11_add_module(core ${SRC_FILES})
target_link_libraries(core PRIVATE tampl pybind11::module)
target_include_directories(
  core
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

install(TARGETS core DESTINATION pytampl/core)
