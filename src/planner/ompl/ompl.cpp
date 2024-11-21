#include "tampl/planner/ompl/ompl.hpp"

namespace tampl::planner::ompl {

OMPL::OMPL(const std::string &planner_id) {
  printf("Creating OMPL planner with ID: %s\n", planner_id.c_str());
}

bool OMPL::solve(const std::shared_ptr<core::Agent> &agent,
                 const std::shared_ptr<core::state::State> &goal) {

  // cast agent into ompl-specific agent
  auto ompl_agent = std::dynamic_pointer_cast<agent::OMPLAgent>(agent);
  if (!ompl_agent) {
    std::cerr << "Failed to cast the input agent to agent::OMPLAgent. Make "
                 "sure you are passing an instance of agent::OMPLAgent "
                 "type\n";
    return false;
  }

  // get the type of TAMPL's space space
  auto tampl_ss = ompl_agent->get_state_space();

  // get space information from the agent
  auto si = ompl_agent->get_space_information();

  // create a planner for the defined space
  // TODO: make use of planner_id
  auto planner = std::make_shared<::ompl::geometric::RRTConnect>(si);

  // get the problem we are trying to solve for the planner
  auto pdef = ompl_agent->get_problem_definition();

  // set the goal state
  pdef->setGoalState(conversions::to_ompl_state(goal, si, tampl_ss));
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
    auto solution =
        pdef->getSolutionPath()->as<::ompl::geometric::PathGeometric>();
    std::cout << "Found solution:" << std::endl;

    // print the path to screen
    solution->print(std::cout);
    // Interpolate ("approx to collision checking resolution").
    solution->interpolate();
    // Get the solution states.
    auto solutionStates = solution->getStates();

    for (size_t i = 0; i < solutionStates.size() - 1; ++i) {
      if (tampl_ss->type == core::state_space::Type::Rn) {
        auto from_state =
            std::make_shared<core::state::Real>(tampl_ss->dimensions);
        auto to_state =
            std::make_shared<core::state::Real>(tampl_ss->dimensions);
        for (auto j = 0u; j < tampl_ss->dimensions; ++j) {
          from_state->operator[](j) =
              solutionStates[i]
                  ->as<::ompl::base::RealVectorStateSpace::StateType>()
                  ->
                  operator[](j);
          to_state->operator[](j) =
              solutionStates[i + 1]
                  ->as<::ompl::base::RealVectorStateSpace::StateType>()
                  ->
                  operator[](j);
        }
        plan_.emplace_back(from_state, to_state);
      }
    }
  } else
    std::cout << "No solution found" << std::endl;

  return true;
}

} // namespace tampl::planner::ompl
