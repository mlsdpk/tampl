/*
 * This example demonstrates a simple task planning setup using PDDL.
 * It showcases how to load a domain and problem, and use the Fast Downward planner
 * to generate a solution plan.
 */

#include <memory>

#include "tampl/tampl.hpp"

int main(int argc, char const *argv[]) {

  // Step 1: Create domain and problem instances from PDDL files
  auto domain = std::make_shared<tampl::core::Domain>("data/pddl/task/lets_eat/domain.pddl");
  auto problem = std::make_shared<tampl::core::Problem>("data/pddl/task/lets_eat/problem.pddl");

  // Step 2: Create a Fast Downward task planner
  // This planner will attempt to generate a valid plan based on the given domain and problem.
  auto task_planner = std::make_shared<tampl::planner::FastDownward>();

  // Step 3: Solve the task planning problem
  // If a solution is found, it will contain a sequence of actions to achieve the goal.
  auto solution = task_planner->solve(domain->get_file_path(), problem->get_file_path());

  // if solution is found, output it on the console
  if (solution)
  {
    TAMPL_INFO("Task planner found a solution plan with {} actions", (*solution).size());
    for (size_t i = 0; i < (*solution).size(); ++i)
    {
      TAMPL_INFO("[{}] action id: {}", i, (*solution)[i]->get_id());
    }
  }
  else
  {
    // if no solution is found, inform the user.
    TAMPL_ERROR("Solution not found");
  }

  return 0;
}
