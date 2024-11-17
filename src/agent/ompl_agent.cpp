#include "tampl/agent/ompl_agent.hpp"

namespace tampl::agent {

OMPLAgent::OMPLAgent(
    const std::string &id,
    const std::shared_ptr<core::state_space::StateSpace> &state_space)
    : state_space_(state_space), core::Agent(id) {

  // get the type and dimensions of TAMPL's space space from given input
  state_space_type_ = state_space->type;
  ndim_ = state_space->dimensions;

  // construct the OMPL's state space we are planning in (Rn, SE2, SE3)
  std::shared_ptr<ompl::base::StateSpace> space;
  if (state_space_type_ == core::state_space::Type::Rn) {
    // create OMPL real vector state space
    space = std::make_shared<ompl::base::RealVectorStateSpace>(ndim_);

    // cast TAMPL generic state space into real state space type
    auto tampl_state_space =
        std::dynamic_pointer_cast<core::state_space::RealStateSpace>(
            state_space);

    // set OMPL state space bounds
    ompl::base::RealVectorBounds bounds(tampl_state_space->dimensions);
    for (size_t i = 0; i < tampl_state_space->dimensions; ++i) {
      bounds.setLow(i, tampl_state_space->bounds[i].first);
      bounds.setHigh(i, tampl_state_space->bounds[i].second);
    }
    space->as<ompl::base::RealVectorStateSpace>()->setBounds(bounds);
  } else if (state_space_type_ == core::state_space::Type::SE2) {
    space = std::make_shared<ompl::base::SE2StateSpace>();
  } else if (state_space_type_ == core::state_space::Type::SE3) {
    space = std::make_shared<ompl::base::SE3StateSpace>();
  } else {
    throw std::invalid_argument(
        "OMPLAgent only supports Rn, SE2 and SE3 state spaces");
  }

  // construct an instance of space information from this state space
  si_ = std::make_shared<ompl::base::SpaceInformation>(space);

  // set state validity checking for this space
  si_->setStateValidityChecker(
      std::bind(&OMPLAgent::is_state_valid, this, std::placeholders::_1));

  // create a problem instance
  pdef_ = std::make_shared<ompl::base::ProblemDefinition>(si_);
}

std::shared_ptr<core::state::State> OMPLAgent::get_random_state() const {
  ompl::base::ScopedState<> state(si_->getStateSpace());
  state.random();

  // cast this into appropriate state type
  if (state_space_type_ == core::state_space::Type::Rn) {
    // create tampl Rn state
    auto tampl_state = std::make_shared<core::state::Real>(ndim_);
    for (size_t i = 0; i < ndim_; ++i) {
      (*tampl_state)[i] = state[i];
    }
    return tampl_state;
  } else {
    throw std::runtime_error("OMPLAgent only supports Rn state space.");
  }
}

void OMPLAgent::set_start_and_goal_states(
    const std::shared_ptr<core::state::State> &start,
    const std::shared_ptr<core::state::State> &goal) {

  if (state_space_type_ == core::state_space::Type::Rn) {
    ompl::base::ScopedState<> ompl_start(si_->getStateSpace());
    ompl::base::ScopedState<> ompl_goal(si_->getStateSpace());
    auto tampl_start_state =
        std::dynamic_pointer_cast<core::state::Real>(start);
    for (size_t i = 0; i < tampl_start_state->size(); ++i) {
      ompl_start[i] = (*tampl_start_state)[i];
    }

    auto tampl_goal_state = std::dynamic_pointer_cast<core::state::Real>(goal);
    for (size_t i = 0; i < tampl_goal_state->size(); ++i) {
      ompl_goal[i] = (*tampl_goal_state)[i];
    }

    // set the start and goal states
    pdef_->setStartAndGoalStates(ompl_start, ompl_goal);
  } else {
    throw std::runtime_error("OMPLAgent only supports Rn state space.");
  }
}

bool OMPLAgent::is_state_valid(const ompl::base::State *state) {
  // cast this into appropriate state type
  if (state_space_type_ == core::state_space::Type::Rn) {
    // downcast state into ompl RealVectorStateSpace type
    const auto *ompl_state =
        state->as<ompl::base::RealVectorStateSpace::StateType>();

    // create tampl Rn state
    auto tampl_state = std::make_shared<core::state::Real>(ndim_);
    for (size_t i = 0; i < ndim_; ++i) {
      (*tampl_state)[i] = (*ompl_state)[i];
    }
    return state_validity_checking_fn_(tampl_state);
  } else {
    throw std::runtime_error("OMPLAgent only supports Rn state space.");
  }

  return false;
}

} // namespace tampl::agent