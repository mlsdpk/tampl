#include "tampl/bt/plugins/decorators/loop_task_plan.hpp"

#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory) {
  BT::NodeBuilder builder = [](const std::string &name,
                               const BT::NodeConfiguration &config) {
    return std::make_unique<BT::LoopNode<std::shared_ptr<tampl::core::Action>>>(name, config);
  };
  factory.registerBuilder<BT::LoopNode<std::shared_ptr<tampl::core::Action>>>("LoopTaskPlan", builder);
}
