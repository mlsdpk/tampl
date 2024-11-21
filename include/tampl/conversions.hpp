#pragma once

#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <iostream> // to remove

// ompl related
#include <ompl/base/SpaceInformation.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/geometric/SimpleSetup.h>

// tampl related
#include "tampl/core/action.hpp"
#include "tampl/core/state.hpp"

namespace tampl::conversions {

inline void from_ff_result(const std::string &from,
                           std::vector<tampl::core::Action> &to) {
  std::string lower_case_result = from;
  std::transform(lower_case_result.begin(), lower_case_result.end(),
                 lower_case_result.begin(), ::tolower);

  std::cout << "from_ff_result: " << lower_case_result << std::endl;

  std::vector<std::string> steps;

  // Regex to find "found legal plan"
  std::regex plan_regex("found legal plan");
  // Regex to match each step action (after "step <number>:")
  std::regex step_regex(
      R"(\d+:\s+([a-z-]+)\s+((?:[a-z0-9-]+\s*)+)(?:$|(?=\n)))");

  // Check if "found legal plan" exists in the lowercase output
  if (std::regex_search(lower_case_result, plan_regex)) {
    // Find all steps matching the step_regex
    auto begin = std::sregex_iterator(lower_case_result.begin(),
                                      lower_case_result.end(), step_regex);
    auto end = std::sregex_iterator();
    for (std::sregex_iterator i = begin; i != end; ++i) {
      std::smatch match = *i;

      tampl::core::Action _action;

      // set action type
      _action.set_type(match[1].str());

      // set action parameters
      std::istringstream iss(match[2].str());
      std::vector<std::string> params;
      std::string param;
      while (iss >> param) {
        params.push_back(param);
      }
      _action.set_parameters(std::move(params));

      // add action back into solution
      to.push_back(std::move(_action));
    }
  }
}

inline ompl::base::ScopedState<>
to_ompl_state(const std::shared_ptr<core::state::State> &state,
              const std::shared_ptr<ompl::base::SpaceInformation> &ompl_si,
              const std::shared_ptr<core::state_space::StateSpace> &tampl_ss) {
  ompl::base::ScopedState<> ompl_state(ompl_si->getStateSpace());

  auto state_space_type = tampl_ss->type;
  if (state_space_type == core::state_space::Type::Rn) {
    auto tampl_state = std::dynamic_pointer_cast<core::state::Real>(state);
    for (size_t i = 0; i < tampl_state->size(); ++i) {
      ompl_state[i] = (*tampl_state)[i];
    }
  }

  return ompl_state;
}

} // namespace tampl::conversions