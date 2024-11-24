#pragma once

#include "tampl/conversions.hpp"
#include "tampl/core/planner.hpp"
#include "tampl/environment/pddl_env.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

namespace tampl::planner {

class FastDownward : public core::Planner {
public:
  FastDownward();

private:
  std::string binary_path_;
  std::string result_;
};

} // namespace tampl::planner