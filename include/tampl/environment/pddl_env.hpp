#pragma once

#include "tampl/core/environment.hpp"
#include "tampl/pddl/domain.hpp"
#include "tampl/pddl/problem.hpp"

namespace tampl::environment {
class PDDLEnvironment : public core::Environment {
public:
  PDDLEnvironment() = delete;
  explicit PDDLEnvironment(const std::string &name,
                           const std::string &domain_file_path,
                           const std::string &problem_file_path);

  pddl::Domain &pddl_domain() { return domain_; }
  const pddl::Domain &pddl_domain() const { return domain_; }

  pddl::Problem &pddl_problem() { return problem_; }
  const pddl::Problem &pddl_problem() const { return problem_; }

private:
  pddl::Domain domain_;
  pddl::Problem problem_;
};

} // namespace tampl::environment