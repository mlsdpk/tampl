#pragma once

#include "behaviortree_cpp/behavior_tree.h"

#include "tampl/core/action.hpp"
#include "tampl/core/state.hpp"
#include "tampl/logger.hpp"

namespace tampl::bt {

/**
 * @brief BT action node to store the task action and motion plan in the plan
 * skeleton storage.
 */
class AddToPlanSkeleton : public BT::SyncActionNode {
public:
  AddToPlanSkeleton(const std::string &name,
                    const BT::NodeConfiguration &config);

  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts();

private:
  using task_action_t = std::shared_ptr<core::Action>;
  using motion_plan_t = std::vector<core::state::State>;
  using plan_skeleton_t = std::vector<std::pair<task_action_t, motion_plan_t>>;
};
} // namespace tampl::bt
