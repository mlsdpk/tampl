#include "tampl/bt/plugins/actions/add_to_plan_skeleton.hpp"

namespace tampl::bt {

AddToPlanSkeleton::AddToPlanSkeleton(const std::string &name,
                                     const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::PortsList AddToPlanSkeleton::providedPorts() {
  return {BT::BidirectionalPort<plan_skeleton_t>("plan"),
          BT::InputPort<task_action_t>("task_action", nullptr, "TODO"),
          BT::InputPort<motion_plan_t>("motion_plan", motion_plan_t{}, "TODO")};
}

BT::NodeStatus AddToPlanSkeleton::tick() {
  BT::Expected<task_action_t> task_action =
      getInput<task_action_t>("task_action");
  // Check if expected is valid. If not, throw its error
  if (!task_action) {
    throw BT::RuntimeError("missing required input [message]: ",
                           task_action.error());
  }

  TAMPL_DEBUG("AddToPlanSkeleton::tick() received 'task_action' with id '{}'", task_action.value()->get_id());

  BT::Expected<motion_plan_t> motion_plan =
      getInput<motion_plan_t>("motion_plan");
  // Check if expected is valid. If not, throw its error
  if (!motion_plan) {
    throw BT::RuntimeError("missing required input [message]: ",
                           motion_plan.error());
  }

  TAMPL_DEBUG("AddToPlanSkeleton::tick() received 'motion_plan' with {} states", motion_plan.value().size());

  if (auto any_ptr = getLockedPortContent("plan")) {
    // inside this scope (as long as any_ptr exists) the access to
    // the entry in the blackboard is mutex-protected and thread-safe.

    // check if the entry contains a valid element
    if (any_ptr->empty()) {
      // The entry hasn't been initialized by any other node, yet.
      // Let's initialize it ourselves
      TAMPL_DEBUG("Initializing plan skeleton for the first time...");
      plan_skeleton_t plan = {std::make_pair(task_action.value(), motion_plan.value())};
      any_ptr.assign(plan);
    } else if (auto *vect_ptr = any_ptr->castPtr<plan_skeleton_t>()) {
      // NOTE: vect_ptr would be nullptr, if we try to cast it to the wrong type
      TAMPL_DEBUG("Adding new task and motion plan into previous plan skeleton");
      vect_ptr->push_back(std::make_pair(task_action.value(), motion_plan.value()));
    }
    return BT::NodeStatus::SUCCESS;
  }

  return BT::NodeStatus::FAILURE;
}

} // namespace tampl::bt

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory) {
  BT::NodeBuilder builder = [](const std::string &name,
                               const BT::NodeConfiguration &config) {
    return std::make_unique<tampl::bt::AddToPlanSkeleton>(name, config);
  };
  factory.registerBuilder<tampl::bt::AddToPlanSkeleton>("AddToPlanSkeleton",
                                                        builder);
}
