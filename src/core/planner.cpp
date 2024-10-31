#include "tampl/core/planner.hpp"

namespace tampl::core {
const std::vector<tampl::core::Action> &Planner::get_solution() const {
  return plan_;
}
} // namespace tampl::core
