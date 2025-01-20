set(_environment_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp_environment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environment_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environment_manager.cpp)

if(TAMPL_BUILD_PYBINDINGS)
    list(APPEND _environment_src_files ${CMAKE_CURRENT_SOURCE_DIR}/py_environment.cpp)
endif()

set(_environment_src_files ${_environment_src_files} PARENT_SCOPE)