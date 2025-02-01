include(cmake/CPM.cmake)

CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.13.0")

CPMAddPackage(
  NAME ompl
  GITHUB_REPOSITORY ompl/ompl
  GIT_TAG prerelease
  OPTIONS
      "OMPL_BUILD_TESTS OFF"
      "OMPL_BUILD_DEMOS OFF"
      "OMPL_BUILD_PYBINDINGS OFF"
      "OMPL_BUILD_PYTESTS OFF"
)

CPMAddPackage(
  NAME behaviortree_cpp
  GITHUB_REPOSITORY BehaviorTree/BehaviorTree.CPP
  GIT_TAG 4.6.2
  VERSION 4.6.2
  OPTIONS
      "BTCPP_UNIT_TESTS OFF"
      "BTCPP_EXAMPLES OFF"
)

CPMAddPackage(
  NAME yaml-cpp
  GITHUB_REPOSITORY jbeder/yaml-cpp
  GIT_TAG 0.8.0
  VERSION 0.8.0
  OPTIONS
    "YAML_CPP_BUILD_TESTS OFF"
    "YAML_CPP_BUILD_CONTRIB OFF"
    "YAML_CPP_BUILD_TOOLS OFF"
    "YAML_CPP_INSTALL ON"
)

CPMAddPackage(
  NAME downward
  GITHUB_REPOSITORY aibasel/downward
  GIT_TAG release-24.06.0
  DOWNLOAD_ONLY YES
)
if (downward_ADDED)
  # Copy the translator into the output directory
  add_custom_target(translate ALL)
  add_custom_command(TARGET translate POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${downward_SOURCE_DIR}/src/translate
          ${downward_BINARY_DIR}/translate
      COMMENT "Copying translator module into output directory")

  # Copy fast-downward.py script
  add_custom_target(copy_fast_downward ALL)
  add_custom_command(TARGET copy_fast_downward POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${downward_SOURCE_DIR}/fast-downward.py
          ${downward_BINARY_DIR}/fast-downward.py
      COMMENT "Copying fast-downward.py into output directory")

  # Copy the driver into the output directory
  add_custom_target(copy_driver ALL)
  add_custom_command(TARGET copy_driver POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${downward_SOURCE_DIR}/driver
          ${downward_BINARY_DIR}/driver
      COMMENT "Copying driver module into output directory")

  # Add search component as a subproject.
  add_subdirectory(${downward_SOURCE_DIR}/src/search ${downward_BINARY_DIR}) 
endif()
