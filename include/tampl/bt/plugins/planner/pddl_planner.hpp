#pragma once

#include <deque>

#include "behaviortree_cpp/behavior_tree.h"
// #include "tampl/planner/fast_forward/fast_forward.hpp"

#include "tampl/core/action.hpp"

namespace tampl::bt::planner {

/**
 * @class PDDLPlanner
 * @brief This class represents a behavior tree action node that uses a
 * PDDL-based planner.
 *
 * The `PDDLPlanner` class is a custom action node for a behavior tree, which
 * integrates popular PDDL-based planners such as FastForward, FastDownward etc,
 * to generate a sequence of tampl's actions (a plan).
 */
class PDDLPlanner : public BT::SyncActionNode {
public:
  /**
   * @brief Constructs a PDDLPlanner node with the given name and configuration.
   * @param name The name of the node.
   * @param config The configuration for the node, provided by the behavior tree
   * framework.
   */
  PDDLPlanner(const std::string &name, const BT::NodeConfiguration &config);

  /**
   * @brief Performs a tick by invoking the planner and returns the status.
   * @return The status of the tick, which indicates whether the planning
   * succeeded or failed.
   */
  BT::NodeStatus tick() override;

  /**
   * @brief Provides the list of ports required by this BT action node.
   * @return A list of ports used by the node, as defined by the behavior tree
   * framework.
   */
  static BT::PortsList providedPorts();

private:
  /// @brief Instance of the planner used for planning.
  /// @todo(Phone): change this to PDDL specific planner class
  // std::unique_ptr<tampl::planner::FastForward> planner_;
};
} // namespace tampl::bt::planner