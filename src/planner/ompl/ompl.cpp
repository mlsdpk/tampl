#include "tampl/planner/ompl/ompl.hpp"

namespace tampl::planner::ompl {

OMPL::OMPL(const std::string &planner_id) {
  printf("Creating OMPL planner with ID: %s\n", planner_id.c_str());
}

bool OMPL::solve(const std::shared_ptr<core::Environment> &env) {

  // cast env into ompl-specific environment
  auto ompl_env = std::dynamic_pointer_cast<environment::OMPLEnvironment>(env);
  if (!ompl_env) {
    std::cerr
        << "Failed to cast the input env to environment::OMPLEnvironment. Make "
           "sure you are passing an instance of environment::OMPLEnvironment "
           "type\n";
    return false;
  }

  // get space information from the env
  auto si = ompl_env->get_space_information();

  // create a planner for the defined space
  // TODO: make use of planner_id
  auto planner = std::make_shared<::ompl::geometric::RRTConnect>(si);

  // get the problem we are trying to solve for the planner
  auto pdef = ompl_env->get_problem_definition();
  planner->setProblemDefinition(pdef);

  // perform setup steps for the planner
  planner->setup();

  // print the settings for this space
  si->printSettings(std::cout);

  // print the problem settings
  pdef->print(std::cout);

  // attempt to solve the problem within one second of planning time
  ::ompl::base::PlannerStatus solved =
      planner->::ompl::base::Planner::solve(1.0);

  if (solved) {
    // get the goal representation from the problem definition (not the same as
    // the goal state) and inquire about the found path
    ::ompl::base::PathPtr path = pdef->getSolutionPath();
    std::cout << "Found solution:" << std::endl;

    // print the path to screen
    path->print(std::cout);
  } else
    std::cout << "No solution found" << std::endl;

  return true;
}

} // namespace tampl::planner::ompl
