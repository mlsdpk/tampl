#include "tampl/environment/ompl_env.hpp"

namespace tampl::environment {

OMPLEnvironment::OMPLEnvironment(const std::string &name)
    : core::Environment(name) {

  // setup robot instance

  // construct the state space we are planning in (Rn, SE2, SE3)
  // TODO: this should be selected based on robot instance
  auto space(std::make_shared<ompl::base::SE3StateSpace>());

  // set the bounds for the R^3 part of SE(3)
  // TODO: this should be selected based on robot instance
  ompl::base::RealVectorBounds bounds(3);
  bounds.setLow(-1);
  bounds.setHigh(1);

  space->setBounds(bounds);

  // construct an instance of space information from this state space
  si_ = std::make_shared<ompl::base::SpaceInformation>(space);

  // set state validity checking for this space
  si_->setStateValidityChecker(
      std::bind(&OMPLEnvironment::is_state_valid, this, std::placeholders::_1));

  // create a problem instance
  pdef_ = std::make_shared<ompl::base::ProblemDefinition>(si_);

  // create a random start state
  ompl::base::ScopedState<> start(space);
  start.random();

  // create a random goal state
  ompl::base::ScopedState<> goal(space);
  goal.random();

  // set the start and goal states
  pdef_->setStartAndGoalStates(start, goal);
}

bool OMPLEnvironment::is_state_valid(const ompl::base::State *state) {
  // cast the abstract state type to the type we expect
  const auto *se3state = state->as<ompl::base::SE3StateSpace::StateType>();

  // extract the first component of the state and cast it to what we expect
  const auto *pos =
      se3state->as<ompl::base::RealVectorStateSpace::StateType>(0);

  // extract the second component of the state and cast it to what we expect
  const auto *rot = se3state->as<ompl::base::SO3StateSpace::StateType>(1);

  // check validity of state defined by pos & rot

  // return a value that is always true but uses the two variables we define, so
  // we avoid compiler warnings
  return (const void *)rot != (const void *)pos;
}

} // namespace tampl::environment