#include "tampl/bt/planner_bt_engine.hpp"

namespace tampl::bt {

PlannerBTEngine::PlannerBTEngine(
      const std::string &bt_xml_path,
      const std::shared_ptr<core::Domain> &domain,
      const std::shared_ptr<core::Problem> &problem)
  : bt_xml_path_{bt_xml_path}, domain_{domain}, problem_{problem} {

  // ref: nav2_util/string_utils.hpp
  auto split = [](const std::string &tokenstring, char delimiter) {
    std::vector<std::string> tokens;

    size_t current_pos = 0;
    size_t pos = 0;
    while ((pos = tokenstring.find(delimiter, current_pos)) !=
           std::string::npos) {
      tokens.push_back(tokenstring.substr(current_pos, pos - current_pos));
      current_pos = pos + 1;
    }
    tokens.push_back(tokenstring.substr(current_pos));
    return tokens;
  };

  auto plugin_libs = split(tampl::bt::TAMPL_DEFAULT_BT_PLUGINS, ';');

  for (const auto &p : plugin_libs) {

    // we'll find default plugins from install directory first
    std::filesystem::path abs_path_to_plugin =
      std::filesystem::path(tampl::bt::TAMPL_DEFAULT_BT_PLUGINS_INSTALL_DIR) / BT::SharedLibrary::getOSName(p);
    if (std::filesystem::exists(abs_path_to_plugin))
    {
      bt_factory_.registerFromPlugin(abs_path_to_plugin.string());
      continue;
    }

    // fallback to build directory
    abs_path_to_plugin =
      std::filesystem::path(tampl::bt::TAMPL_DEFAULT_BT_PLUGINS_BUILD_DIR) / BT::SharedLibrary::getOSName(p);
    if (std::filesystem::exists(abs_path_to_plugin))
    {
      bt_factory_.registerFromPlugin(abs_path_to_plugin.string());
    } else {
      TAMPL_WARN("BT plugin {} not found in either BUILD or INSTALL directories.", p);
    }

  }
}

PlannerBTEngine::~PlannerBTEngine() {}

bool PlannerBTEngine::init() {

  // get PDDL domain and problem
  const std::string& domain_file = domain_->get_file_path().string();
  const std::string& problem_file = problem_->get_file_path().string();

  TAMPL_INFO(
    "[PlannerBTEngine] Using PDDL domain from {} and problem from {}", domain_file, problem_file);

  // TODO: sanity check whether all the actions in the domain are available in the
  // environment to execute
  //
  // const auto &action_ids = domain->get_action_ids();
  // for (const auto &id : action_ids) {
  //   if (!env_manager_->has_action(id)) {
  //     printf("[PlannerBTEngine]: Unable to find the action '%s' in the "
  //            "environment. Have you registered the actions correctly?",
  //            id.c_str());
  //     return false;
  //   }
  // }

  bb_ = BT::Blackboard::create();
  bb_->set<std::string>("domain_file", domain_file);
  bb_->set<std::string>("problem_file", problem_file);

  tree_ = bt_factory_.createTreeFromFile(bt_xml_path_, bb_);

  initialized_ = true;
  return initialized_;
}

bool PlannerBTEngine::solve() {
  if (!initialized_)
    return false;

  // To "execute" a Tree you need to "tick" it.
  // The tick is propagated to the children based on the logic of the tree.
  // In this case, the entire sequence is executed, because all the children
  // of the Sequence return SUCCESS.
  auto status = tree_.tickWhileRunning();
  plan_ = tree_.rootBlackboard()->get<plan_skeleton_t>("plan");

  return (status == BT::NodeStatus::SUCCESS) ? true : false;
}

bool PlannerBTEngine::execute(const plan_skeleton_t &plan) {
  if (!initialized_)
    return false;

  // TODO(Phone): create a BT from the plan and execute it

  // Temporary execution logic
  // for (const auto &action_id : plan) {
  //   // attempt to execute the action
  //   if (!env_manager_->execute(action_id)) {
  //     printf("[PlannerBTEngine]: Failed to execute action '%s'",
  //            action_id.c_str());
  //     return false;
  //   }
  // }

  TAMPL_INFO("Executing the planning solution sequentially...");
  for (const auto& [task_action, motion_plan] : plan)
  {
    TAMPL_INFO("Running task action '{}'", task_action->get_id());
    if (!domain_->execute(task_action->get_id()))
    {
      TAMPL_ERROR("Failed to execute task action '{}'", task_action->get_id());
      TAMPL_ERROR("Planning failed");
      return false;
    }
  }

  TAMPL_INFO("Planning finished successfully");

  return true;
}

const PlannerBTEngine::plan_skeleton_t &PlannerBTEngine::get_plan() const {
  // get the plan skeleton from the main blackboard
  return plan_;
}

} // namespace tampl::bt
