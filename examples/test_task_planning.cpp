#include "tampl/tampl.hpp"

int main(int argc, char const *argv[]) {

  // create FF and FD planners
  auto ffplanner = std::make_unique<tampl::planner::FastForward>();
  auto fdplanner = std::make_unique<tampl::planner::FastDownward>();

  return 0;
}