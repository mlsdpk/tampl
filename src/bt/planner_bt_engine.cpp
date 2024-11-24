#include "tampl/bt/planner_bt_engine.hpp"

namespace tampl::bt {

PlannerBTEngine::PlannerBTEngine(const std::string &bt_xml_path,
                                 const std::string &domain_file,
                                 const std::string &problem_file) {
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

  bb_ = BT::Blackboard::create();
  bb_->set<std::string>("domain_file", domain_file);
  bb_->set<std::string>("problem_file", problem_file);

  tree_ = bt_factory_.createTreeFromFile(bt_xml_path, bb_);
}

PlannerBTEngine::~PlannerBTEngine() {}

bool PlannerBTEngine::run() {
  // To "execute" a Tree you need to "tick" it.
  // The tick is propagated to the children based on the logic of the tree.
  // In this case, the entire sequence is executed, because all the children
  // of the Sequence return SUCCESS.
  auto status = tree_.tickWhileRunning();

  if (status == BT::NodeStatus::SUCCESS)
    plan_ = tree_.rootBlackboard()->get<std::vector<core::Action>>("plan");

  return true;
}

const std::vector<core::Action> &PlannerBTEngine::get_plan() const {
  return plan_;
}

} // namespace tampl::bt