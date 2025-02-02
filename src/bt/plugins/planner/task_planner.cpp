#include "tampl/bt/plugins/planner/task_planner.hpp"

namespace tampl::bt::planner {

TaskPlanner::TaskPlanner(const std::string &name,
                         const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::PortsList TaskPlanner::providedPorts() {
  return {BT::InputPort<std::string>("id"),
          BT::InputPort<std::string>("domain_file"),
          BT::InputPort<std::string>("problem_file"),
          BT::OutputPort<BT::SharedQueue<tampl::core::Action>>("plan")};
}

BT::NodeStatus TaskPlanner::tick() {
  std::cout << "TaskPlanner: " << this->name() << std::endl;

  BT::Expected<std::string> planner_id = getInput<std::string>("id");
  // Check if expected is valid. If not, throw its error
  if (!planner_id) {
    throw BT::RuntimeError("missing required input [message]: ",
                           planner_id.error());
  }

  if (planner_id == "FastDownward") {
    planner_ = std::make_unique<tampl::planner::FastDownward>();
  } else {
    std::cout << "Unsupported planner id provided. Only FastDownward is "
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

  // bool solved = planner_->solve(domain_file.value(), problem_file.value());

  // if (solved) {
  //   const auto &plan = planner_->get_solution();
  //   setOutput("plan", plan);
  // }

  bool solved = true;

  return solved ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

} // namespace tampl::bt::planner

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory) {
  BT::NodeBuilder builder = [](const std::string &name,
                               const BT::NodeConfiguration &config) {
    return std::make_unique<tampl::bt::planner::TaskPlanner>(name, config);
  };
  factory.registerBuilder<tampl::bt::planner::TaskPlanner>("TaskPlanner",
                                                           builder);
}
