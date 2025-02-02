set(FD_PLANNER_EXECUTABLE_BUILD "${downward_BINARY_DIR}/fast-downward.py")
set(FD_PLANNER_EXECUTABLE_INSTALL "") # FIXME: I do not have 'install' yet

# Pass both build and install paths to the library
target_compile_definitions(
  tampl
  PRIVATE FD_PLANNER_EXECUTABLE_BUILD="${FD_PLANNER_EXECUTABLE_BUILD}"
          FD_PLANNER_EXECUTABLE_INSTALL="${FD_PLANNER_EXECUTABLE_INSTALL}")
