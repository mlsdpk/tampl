#pragma once

#include <memory>
#include <string>
#include <vector>

#include "tampl/core/action.hpp"
#include "tampl/core/environment.hpp"
#include "tampl/pddl/domain.hpp"
#include "tampl/pddl/problem.hpp"

namespace tampl::core {

class Planner {
public:
  Planner() = default;
  explicit Planner(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Planner() = default;

  virtual bool solve(const std::shared_ptr<Environment> &env) = 0;
  const std::vector<tampl::core::Action> &get_solution() const;

protected:
  std::vector<tampl::core::Action> plan_;
};

} // namespace tampl::core