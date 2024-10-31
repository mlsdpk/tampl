#pragma once

#include <string>

namespace tampl::core {

class Environment {
public:
  Environment() = default;
  explicit Environment(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Environment() = default;
};

} // namespace tampl::core