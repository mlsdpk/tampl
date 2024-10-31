#include "tampl/environment/pddl_env.hpp"

namespace tampl::environment {

PDDLEnvironment::PDDLEnvironment(const std::string &name,
                                 const std::string &domain_file_path,
                                 const std::string &problem_file_path)
    : core::Environment(name), domain_(domain_file_path),
      problem_(problem_file_path) {}

} // namespace tampl::environment