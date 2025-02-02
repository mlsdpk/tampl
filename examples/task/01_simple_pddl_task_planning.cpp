#include "tampl/tampl.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char const *argv[]) {

  // create domain and problem instances from pddl files
  auto domain = std::make_shared<tampl::core::Domain>(
     "../../examples/task/pddl/lets_eat/domain.pddl");
  auto problem = std::make_shared<tampl::core::Problem>(
    "../../examples/task/pddl/lets_eat/problem.pddl");

  // we need to make sure each action in the domain has associated executors
  domain->register_action("pick-up",[](){ std::cout << "Executing action 'pick-up'\n"; });
  domain->register_action("drop", [](){ std::cout << "Executing action 'drop'\n"; });
  domain->register_action("move", [](){ std::cout << "Executing action 'move'\n"; });

  // create planner BT engine
  auto bt_xml_path = tampl::bt::default_behavior_trees_dir() / "task/simple_task_planner.xml";
  auto engine = std::make_shared<tampl::bt::PlannerBTEngine>(bt_xml_path.string(), domain, problem);

  // run the planner (this will only find a solution plan 
  // and do not execute each registered action callbacks)
  bool solved = engine->solve();

  if (solved)
  {
    // get the solution
    auto plan = engine->get_plan();

    // execute the solution plan
    engine->execute(plan);
  }
  else
  {
    std::cout << "Solution not found\n";
  }

  return 0;
}
