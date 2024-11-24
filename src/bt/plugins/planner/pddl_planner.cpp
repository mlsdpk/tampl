#include "tampl/bt/plugins/planner/pddl_planner.hpp"

namespace tampl::bt::planner {

PDDLPlanner::PDDLPlanner(const std::string &name,
                         const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::PortsList PDDLPlanner::providedPorts() {
  return {BT::InputPort<std::string>("id"),
          BT::InputPort<std::string>("domain_file"),
          BT::InputPort<std::string>("problem_file"),
          BT::OutputPort<std::vector<tampl::core::Action>>("plan")};
}

BT::NodeStatus PDDLPlanner::tick() {
  std::cout << "PDDLPlanner: " << this->name() << std::endl;

  BT::Expected<std::string> planner_id = getInput<std::string>("id");
  // Check if expected is valid. If not, throw its error
  if (!planner_id) {
    throw BT::RuntimeError("missing required input [message]: ",
                           planner_id.error());
  }

  if (planner_id == "FastForward") {
    planner_ = std::make_unique<tampl::planner::FastForward>();
  } else {
    std::cout << "Unsupported planner id provided. Only FastForward is "
                 "supported at the moment!\n";
    return BT::NodeStatus::FAILURE;
  }

  BT::Expected<std::string> domain_file = getInput<std::string>("domain_file");
  // Check if expected is valid. If not, throw its error
  if (!domain_file) {
    throw BT::RuntimeError("missing required input [message]: ",
                           domain_file.error());
  }
  // use the method value() to extract the valid message.
  std::cout << "Domain File: " << domain_file.value() << std::endl;

  BT::Expected<std::string> problem_file =
      getInput<std::string>("problem_file");
  // Check if expected is valid. If not, throw its error
  if (!problem_file) {
    throw BT::RuntimeError("missing required input [message]: ",
                           problem_file.error());
  }
  // use the method value() to extract the valid message.
  std::cout << "Problem File: " << problem_file.value() << std::endl;

  bool solved = planner_->solve(domain_file.value(), problem_file.value());

  if (solved) {
    const auto &plan = planner_->get_solution();
    setOutput("plan", plan);
  }

  return solved ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

} // namespace tampl::bt::planner

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory) {
  BT::NodeBuilder builder = [](const std::string &name,
                               const BT::NodeConfiguration &config) {
    return std::make_unique<tampl::bt::planner::PDDLPlanner>(name, config);
  };
  factory.registerBuilder<tampl::bt::planner::PDDLPlanner>("PDDLPlanner",
                                                           builder);
}