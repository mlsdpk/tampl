#pragma once

#include <string>

namespace tampl::planner {

class Planner {
public:
  Planner() = default;
  explicit Planner(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Planner() = default;
};

} // namespace tampl::planner