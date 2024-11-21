#pragma once

#include <string>

namespace tampl::core {

class Agent {
public:
  Agent() = default;
  explicit Agent(const std::string &id) : id(id) {
    printf("Creating Agent %s\n", id.c_str());
  }
  virtual ~Agent() = default;

  std::string id;
};

} // namespace tampl::core