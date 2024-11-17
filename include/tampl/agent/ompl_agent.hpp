#pragma once

#include <functional>

#include <ompl/base/SpaceInformation.h>
#include <ompl/geometric/SimpleSetup.h>

// ompl - Rn, SE2, SE3 spaces
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/base/spaces/SE3StateSpace.h>

#include "tampl/core/agent.hpp"
#include "tampl/core/state.hpp"

namespace tampl::agent {

class OMPLAgent : public core::Agent {
public:
  OMPLAgent() = delete;
  explicit OMPLAgent(
      const std::string &id,
      const std::shared_ptr<core::state_space::StateSpace> &state_space);

  std::shared_ptr<ompl::base::ProblemDefinition> get_problem_definition() {
    return pdef_;
  }

  std::shared_ptr<ompl::base::SpaceInformation> get_space_information() {
    return si_;
  }

  using state_validity_checking_fn_t =
      std::function<bool(const std::shared_ptr<core::state::State> &)>;
  bool set_state_validity_fn(const state_validity_checking_fn_t &fn) {
    state_validity_checking_fn_ = fn;
  }

  std::shared_ptr<core::state_space::StateSpace> get_state_space() const {
    return state_space_;
  }

  std::shared_ptr<core::state::State> get_random_state() const;

  void
  set_start_and_goal_states(const std::shared_ptr<core::state::State> &start,
                            const std::shared_ptr<core::state::State> &goal);

protected:
  bool is_state_valid(const ompl::base::State *state);

  std::shared_ptr<ompl::base::ProblemDefinition> pdef_;
  std::shared_ptr<ompl::base::SpaceInformation> si_;

  std::shared_ptr<core::state_space::StateSpace> state_space_;
  core::state_space::Type state_space_type_;
  size_t ndim_;

private:
  state_validity_checking_fn_t state_validity_checking_fn_;
};

} // namespace tampl::agent