#pragma once

#include <string>
#include <vector>

#include "tampl/core/state.hpp"

namespace tampl::core {

// TODO: make it templated base class and create PDDL specifc action class
class Action {
public:
  Action() = default;
  Action(const std::shared_ptr<core::state::State> &from_state,
         const std::shared_ptr<core::state::State> &to_state)
      : from_state_(from_state), to_state_(to_state) {}
  virtual ~Action() = default;

  void set_type(const std::string &action_type) { type_ = action_type; }
  void set_parameters(const std::vector<std::string> &parameters) {
    parameters_ = parameters;
  }

  const std::string &get_type() const { return type_; }
  const std::vector<std::string> &get_parameters() const { return parameters_; }

  std::shared_ptr<core::state::State> get_from_state() const {
    return from_state_;
  }
  std::shared_ptr<core::state::State> get_to_state() const { return to_state_; }

private:
  std::string type_;
  std::vector<std::string> parameters_;

  std::shared_ptr<core::state::State> from_state_;
  std::shared_ptr<core::state::State> to_state_;
};

} // namespace tampl::core