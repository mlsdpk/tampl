#include "tampl/core/problem.hpp"

namespace tampl::core
{

Problem::Problem(const std::string& file) : pddl_file_{std::filesystem::path{file}} {}

} // namespace tampl::core

