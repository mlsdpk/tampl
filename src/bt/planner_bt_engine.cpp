#include "tampl/bt/planner_bt_engine.hpp"

namespace tampl::bt {

PlannerBTEngine::PlannerBTEngine(
    const std::string &bt_xml_path,
    const std::shared_ptr<environment::EnvironmentManager> &env_manager)
    : bt_xml_path_{bt_xml_path}, env_manager_{env_manager} {
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
    bt_factory_.registerFromPlugin(BT::SharedLibrary::getOSName(p));
  }
}

PlannerBTEngine::~PlannerBTEngine() {}

bool PlannerBTEngine::init() {
  // get PDDL domain and problem
  const auto &domain = env_manager_->get_domain();
  const auto &problem = env_manager_->get_problem();

  printf("[PlannerBTEngine] Using PDDL domain from %s and problem from %s\n",
         domain->get_file_path().c_str(), problem->get_file_path().c_str());

  // sanity check whether all the actions in the domain are available in the
  // environment to execute
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
  bb_->set<std::string>("domain_file", domain->get_file_path());
  bb_->set<std::string>("problem_file", problem->get_file_path());

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

  // if (status == BT::NodeStatus::SUCCESS)
  //   plan_ = tree_.rootBlackboard()->get<std::vector<core::Action>>("plan");

  return true;
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

  return true;
}

const PlannerBTEngine::plan_skeleton_t &PlannerBTEngine::get_plan() const {
  // get the plan skeleton from the main blackboard
  return bb_->get<plan_skeleton_t>("plan");
}

} // namespace tampl::bt