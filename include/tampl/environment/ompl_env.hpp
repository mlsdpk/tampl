#pragma once

#include <ompl/base/SpaceInformation.h>
#include <ompl/geometric/SimpleSetup.h>

// ompl - Rn, SE2, SE3 spaces
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/base/spaces/SE3StateSpace.h>

#include "tampl/core/environment.hpp"

namespace tampl::environment {

class OMPLEnvironment : public core::Environment {
public:
  OMPLEnvironment() = delete;
  explicit OMPLEnvironment(const std::string &name);

  std::shared_ptr<ompl::base::ProblemDefinition> get_problem_definition() {
    return pdef_;
  }

  std::shared_ptr<ompl::base::SpaceInformation> get_space_information() {
    return si_;
  }

protected:
  bool is_state_valid(const ompl::base::State *state);

  std::shared_ptr<ompl::base::ProblemDefinition> pdef_;
  std::shared_ptr<ompl::base::SpaceInformation> si_;
};

} // namespace tampl::environment