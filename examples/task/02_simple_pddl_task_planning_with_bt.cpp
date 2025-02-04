/*
 * This example demonstrates how to use Behavior Trees (BT) with PDDL in TAMPL for simple task planning.
 * The PDDL (Planning Domain Definition Language) files define the available actions and the problem context,
 * while the BT engine handles planning and execution in a structured manner.
 */

#include <memory>

#include "tampl/tampl.hpp"

int main(int argc, char const *argv[]) {

  // Step 1: Create domain and problem instances from PDDL files
  auto domain = std::make_shared<tampl::core::Domain>("data/pddl/task/lets_eat/domain.pddl");
  auto problem = std::make_shared<tampl::core::Problem>("data/pddl/task/lets_eat/problem.pddl");

  // Step 2: Register action executors
  // Each action in the domain must be associated with a corresponding function (executor)
  // that will be called when the planner executes the action.
  domain->register_action("pick-up",[](){ std::cout << "Executing action 'pick-up'\n"; });
  domain->register_action("drop", [](){ std::cout << "Executing action 'drop'\n"; });
  domain->register_action("move", [](){ std::cout << "Executing action 'move'\n"; });

  // Step 3: Create the Behavior Tree (BT) planner engine
  // The BT engine will load the simple task planning behavior tree XML file
  // from the default set of behavior tree based planners
  auto bt_xml_path = tampl::bt::default_behavior_trees_dir() / "task/simple_task_planner.xml";
  auto engine = std::make_shared<tampl::bt::PlannerBTEngine>(bt_xml_path.string(), domain, problem);

  // Step 4: Initialize the planner BT engine
  // This sets up internal structures and prepares the planner for execution.
  engine->init();

  // Step 5: Solve the task planning problem
  // This step generates a valid plan if a solution exists, but does not execute it yet.
  bool solved = engine->solve();

  if (solved)
  {
    // Step 6: Retrieve the generated plan
    auto plan = engine->get_plan();

    // Step 7: Execute the solution plan
    // Each action in the plan will be executed in order, triggering the registered callbacks.
    engine->execute(plan);
  }
  else
  {
    // if no solution is found, inform the user.
    TAMPL_ERROR("Solution not found");
  }

  return 0;
}
