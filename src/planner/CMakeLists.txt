set(_planner_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_forward/fast_forward.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_downward/fast_downward.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ompl/ompl.cpp
    PARENT_SCOPE)

add_subdirectory(fast_forward)
add_subdirectory(fast_downward)
# add_subdirectory(ompl)
