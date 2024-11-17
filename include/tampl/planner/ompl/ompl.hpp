#pragma once

#include <iostream>

#include "ompl/geometric/planners/rrt/RRTConnect.h"

#include "tampl/agent/ompl_agent.hpp"
#include "tampl/conversions.hpp"
#include "tampl/core/planner.hpp"
#include "tampl/core/state.hpp"

namespace tampl::planner::ompl {

class OMPL : public core::Planner {
public:
  explicit OMPL(const std::string &planner_id);

  bool solve(const std::shared_ptr<core::Agent> &agent,
             const std::shared_ptr<core::state::State> &goal);
};

} // namespace tampl::planner::ompl