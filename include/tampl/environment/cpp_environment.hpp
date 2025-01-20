#pragma once

#include <iostream>
#include <string>

#include "tampl/core/environment.hpp"

namespace tampl::environment {

class CppEnvironment : public EnvironmentInterface {
public:
  CppEnvironment(const std::string &env_name);
  void reset() override;

  std::string get_pddl_domain_file() override { return std::string(""); }
  std::string get_pddl_problem_file() override { return std::string(""); }
};

} // namespace tampl::environment