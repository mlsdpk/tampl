#pragma once

#include <memory>
#include <string>
#include <vector>

#include "tampl/core/action.hpp"

namespace tampl::core {

class Planner {
public:
  Planner() = default;
  explicit Planner(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Planner() = default;

  const std::vector<tampl::core::Action> &get_solution() const;

protected:
  std::vector<tampl::core::Action> plan_;
};

} // namespace tampl::core
