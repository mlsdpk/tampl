#include "tampl/environment/environment_manager.hpp"

namespace tampl::environment {

EnvironmentManager::EnvironmentManager(const std::string &config_file) {
#ifdef TAMPL_BUILD_PYBINDINGS
  // initialize the interpreter if this is executed from C++
  if (!Py_IsInitialized()) {
    interpreter_guard_.emplace();
  }
#endif
  // load the configuration and register environments
  EnvironmentFactory::register_environments(config_file);
}

void EnvironmentManager::init(const std::string &env_name) {
  environment_ = EnvironmentFactory::create(env_name);

  // create domain and problem instances
  // for now get the pddl file paths from the enviornment instance directly
  // TODO(Phone): think about what would be the best way
  // this means all the env instances need to have PDDL domain and problem files
  domain_ =
      std::make_shared<pddl::Domain>(environment_->get_pddl_domain_file());
  problem_ =
      std::make_shared<pddl::Problem>(environment_->get_pddl_problem_file());
}

void EnvironmentManager::reset() {
  if (environment_) {
    environment_->reset();
  }
}

std::shared_ptr<pddl::Domain> EnvironmentManager::get_domain() {
  return domain_;
}

std::shared_ptr<pddl::Problem> EnvironmentManager::get_problem() {
  return problem_;
}

bool EnvironmentManager::has_action(const std::string &id) {

  // this method checks whether action ID is registered inside environment
  // fow now returns true
  // TODO(Phone): implement this

  return true;
}

bool EnvironmentManager::execute(const std::string &id) {
  // main method for action execution
  // return simulator_->execute(id);
}

} // namespace tampl::environment