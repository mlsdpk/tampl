#include "tampl/tampl.hpp"

int main(int argc, char const *argv[]) {

  // create FF and FD planners
  auto ffplanner = std::make_unique<tampl::planner::FastForward>();
  auto fdplanner = std::make_unique<tampl::planner::FastDownward>();

  // create OMPL planner
  using ompl_planner_t = tampl::planner::ompl::OMPL;
  auto ompl_planner = std::make_unique<ompl_planner_t>("RRTConnect");

  return 0;
}