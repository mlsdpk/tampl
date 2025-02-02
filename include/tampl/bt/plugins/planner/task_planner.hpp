#pragma once

#include <deque>

#include "behaviortree_cpp/behavior_tree.h"

#include "tampl/core/action.hpp"
#include "tampl/planner/fast_downward/fast_downward.hpp"

namespace tampl::bt::planner {


class TaskPlanner : public BT::SyncActionNode {
public:

  TaskPlanner(const std::string &name, const BT::NodeConfiguration &config);


  BT::NodeStatus tick() override;


  static BT::PortsList providedPorts();

private:
  /// @brief Instance of the planner used for planning.
  /// @todo(Phone): change this to PDDL specific planner class
  std::unique_ptr<tampl::planner::FastDownward> planner_;
};
} // namespace tampl::bt::planner
