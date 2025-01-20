#pragma once

namespace tampl::environment {

class EnvironmentInterface {
public:
  virtual ~EnvironmentInterface() = default;
  virtual void reset() = 0;

  // TODO: consider changing these to PDDL domain and problem files
  // This means all the envs need to follow PDDL conventions
  virtual std::string get_pddl_domain_file() = 0;
  virtual std::string get_pddl_problem_file() = 0;
};

} // namespace tampl::environment
