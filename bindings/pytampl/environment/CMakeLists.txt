set(SRC_FILES bindings.cpp)

pybind11_add_module(environment ${SRC_FILES})
target_link_libraries(environment PRIVATE tampl pybind11::module)
target_include_directories(
  environment
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>)

install(TARGETS environment DESTINATION pytampl/environment)
