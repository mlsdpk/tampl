#pragma once

#include <string>

// #include "tampl/core/action.hpp"
// #include "tampl/core/state.hpp"

namespace tampl::core {

class Environment {
public:
  Environment() = default;
  explicit Environment(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Environment() = default;

  // /**
  //  * @brief Reset the enviornment.
  //  */
  // virtual void reset() = 0;

  // /**
  //  * @brief Get the current state information.
  //  */
  // virtual std::shared_ptr<core::state::State> get_current_state() const = 0;

  // /**
  //  * @brief Performs a state transition step from current state by applying an
  //  * action to reach to next state.
  //  */
  // virtual bool step(const std::shared_ptr<core::action::Action> &action) = 0;

  // /**
  //  * @brief Check whether applying an action to the given state is
  //  * collision-free or not.
  //  */
  // virtual bool
  // is_valid(const std::shared_ptr<core::state::State> &state,
  //          const std::shared_ptr<core::action::Action> &action) = 0;

  // /**
  //  * @brief Check whether applying an action to current state is collision-free
  //  * or not.
  //  */
  // virtual bool
  // is_valid(const std::shared_ptr<core::action::Action> &action) = 0;

  // /**
  //  * @brief Render the environment (if supported).
  //  */
  // virtual void render() const = 0;
};

} // namespace tampl::core