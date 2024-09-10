#pragma once

#include "pytampl/typedefs.hpp"
#include "tampl/tampl.hpp"

namespace tampl::pytampl {

template <typename StateT = state::State, typename ActionT = action::Action>
class Environment {
public:
  Environment() = default;
  explicit Environment(const std::string &name) {
    printf("Creating environment %s\n", name.c_str());
  }
  virtual ~Environment() = default;

  //   virtual StateT getCurrentState() const = 0;

  //   virtual bool isGoalState(const StateT &state) const = 0;

  //   virtual void executeAction(const ActionT &action) = 0;

  //   virtual std::vector<ActionT> getValidActions(const StateT &state) const =
  //   0;

  //   virtual void reset() = 0;

  //   virtual void render(const std::vector<ActionT> &plan);

  // protected:
  //   StateT m_current_state;
};

} // namespace tampl::pytampl