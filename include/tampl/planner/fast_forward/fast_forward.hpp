#include "tampl/conversions.hpp"
#include "tampl/core/planner.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

namespace tampl::planner {

class FastForward : public core::Planner {
public:
  FastForward();
  bool solve(const pddl::Domain &domain, const pddl::Problem &problem) override;
private:
  std::string binary_path_;
  std::string result_;
};

} // namespace tampl::planner