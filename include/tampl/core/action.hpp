#pragma once

#include <string>
#include <vector>

namespace tampl::core {

// TODO: make it templated base class and create PDDL specifc action class
class Action {
public:
  Action() = default;
  virtual ~Action() = default;

  void set_type(const std::string &action_type) { type_ = action_type; }
  void set_parameters(const std::vector<std::string> &parameters) {
    parameters_ = parameters;
  }

  const std::string &get_type() const { return type_; }
  const std::vector<std::string> &get_parameters() const { return parameters_; }

private:
  std::string type_;
  std::vector<std::string> parameters_;
};

} // namespace tampl::core