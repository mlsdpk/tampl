#pragma once

#include <iostream>

#include "ompl/geometric/planners/rrt/RRTConnect.h"

#include "tampl/core/planner.hpp"
#include "tampl/environment/ompl_env.hpp"

namespace tampl::planner::ompl {

class OMPL : public core::Planner {
public:
  explicit OMPL(const std::string &planner_id);
  bool solve(const std::shared_ptr<core::Environment> &env) override;
};

} // namespace tampl::planner::ompl