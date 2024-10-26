set(HEADER_PATH ${PROJECT_SOURCE_DIR}/bindings/pytampl/environment)

set(HEADER_FILES ${HEADER_PATH}/environment_py.hpp)

set(SRC_FILES environment_py.cpp)

pybind11_add_module(environment ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(environment PRIVATE pybind11::module)
target_include_directories(
  environment
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>
         $<INSTALL_INTERFACE:${TAMPL_INCLUDE_INSTALL_DIR}>
  PRIVATE ${HEADER_PATH})

install(TARGETS environment DESTINATION pytampl/environment)
