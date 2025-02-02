set(_planner_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_downward/fast_downward.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ompl/ompl.cpp
    PARENT_SCOPE)

add_subdirectory(fast_downward)
