#include "tampl/tampl.hpp"

#include <memory>
#include <string>

int main(int argc, char const *argv[]) {

  // path to BT xml
  const std::string bt_xml_path = "behavior_trees/task/task_planner.xml";

  // create TAMPL planner from BT xml
  auto planner = std::make_shared<tampl::bt::PlannerBTEngine>(bt_xml_path, "", "");

  return 0;
}