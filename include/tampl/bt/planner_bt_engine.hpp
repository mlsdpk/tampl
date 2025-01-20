#pragma once

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/utils/shared_library.h"
#include "plugins_list.hpp"

// tampl related
#include "tampl/core/action.hpp"
#include "tampl/environment/environment_manager.hpp"

namespace tampl::bt {

/**
 * @class PlannerBTEngine
 * @brief This class is responsible for running a behavior tree planner engine.
 *
 * The `PlannerBTEngine` class loads and runs a behavior tree (BT) defined in an
 * XML file and provides an interface to retrieve the generated plan as a
 * sequence of TAMPL's actions.
 */
class PlannerBTEngine {
public:
  // TODO(Phone): move the followings into shared location to avoid duplicates
  using task_action_t = std::shared_ptr<core::Action>;
  using motion_plan_t = std::vector<core::state::State>;
  using plan_skeleton_t = std::vector<std::pair<task_action_t, motion_plan_t>>;

  /**
   * @brief Constructs a PlannerBTEngine with a specified behavior tree.
   *
   * @param bt_xml_path Path to the XML file defining the behavior tree.
   * @param env_manager TODO
   */
  PlannerBTEngine(
      const std::string &bt_xml_path,
      const std::shared_ptr<environment::EnvironmentManager> &env_manager);

  /**
   * @brief Destructor for the PlannerBTEngine class.
   */
  ~PlannerBTEngine();

  bool init();

  /**
   * @brief Runs the behavior tree and generates a plan.
   * @return True if the behavior tree was successfully executed, false
   * otherwise.
   */
  bool solve();

  /**
   * @brief
   *
   * @param plan
   * @return
   */
  bool execute(const plan_skeleton_t &plan);

  /**
   * @brief Gets the generated plan as a vector of actions.
   * @return A constant reference to the plan.
   */
  const plan_skeleton_t &get_plan() const;

private:
  /// @brief Factory to create the behavior tree.
  BT::BehaviorTreeFactory bt_factory_;

  /// @brief Behavior tree instance.
  BT::Tree tree_;

  BT::Blackboard::Ptr bb_;

  std::string bt_xml_path_;

  /// @brief
  std::shared_ptr<environment::EnvironmentManager> env_manager_;

  bool initialized_{false};
};

} // namespace tampl::bt