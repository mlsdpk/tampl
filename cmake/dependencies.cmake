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
)