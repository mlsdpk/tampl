#include "tampl/bt/decorators/loop_task_plan.hpp"

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory) {
  BT::NodeBuilder builder = [](const std::string &name,
                               const BT::NodeConfiguration &config) {
    return std::make_unique<BT::LoopNode<tampl::core::Action>>(name, config);
  };
  factory.registerBuilder<BT::LoopNode<tampl::core::Action>>("LoopTaskPlan",
                                                             builder);
}