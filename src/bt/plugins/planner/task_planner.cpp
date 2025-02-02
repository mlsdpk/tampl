#include "tampl/bt/plugins/planner/task_planner.hpp"

namespace tampl::bt::planner {

TaskPlanner::TaskPlanner(const std::string &name,
                         const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::PortsList TaskPlanner::providedPorts() {
  return {BT::InputPort<std::string>("id"),

          // we will use domain and problem files directly from blackboard as default unless it is explicitly given
          // see: https://www.behaviortree.dev/docs/tutorial-advanced/tutorial_12_default_ports#default-blackboard-entry
          BT::InputPort<std::string>("domain_file", "{domain_file}", "TODO"),
          BT::InputPort<std::string>("problem_file", "{problem_file}", "TODO"),

          BT::OutputPort<BT::SharedQueue<std::shared_ptr<tampl::core::Action>>>("task_plan")};
}

BT::NodeStatus TaskPlanner::tick() {

  BT::Expected<std::string> planner_id = getInput<std::string>("id");
  // Check if expected is valid. If not, throw its error
  if (!planner_id) {
    throw BT::RuntimeError("missing required input [message]: ",
                           planner_id.error());
  }

  if (planner_id == "FastDownward") {
    planner_ = std::make_unique<tampl::planner::FastDownward>();
  } else {
    TAMPL_ERROR("Unsupported planner id provided. Only FastDownward is supported at the moment!");
    return BT::NodeStatus::FAILURE;
  }

  BT::Expected<std::string> domain_file = getInput<std::string>("domain_file");
  // Check if expected is valid. If not, throw its error
  if (!domain_file) {
    throw BT::RuntimeError("missing required input [message]: ",
                           domain_file.error());
  }
  // use the method value() to extract the valid message.
  TAMPL_INFO("Domain File: {}", domain_file.value());

  BT::Expected<std::string> problem_file =
      getInput<std::string>("problem_file");
  // Check if expected is valid. If not, throw its error
  if (!problem_file) {
    throw BT::RuntimeError("missing required input [message]: ",
                           problem_file.error());
  }
  // use the method value() to extract the valid message.
  TAMPL_INFO("Problem File: {}", problem_file.value());

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
