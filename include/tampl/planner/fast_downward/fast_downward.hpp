#pragma once

#include "tampl/conversions.hpp"
#include "tampl/core/planner.hpp"
#include "tampl/logger.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>

namespace tampl::planner {

class FastDownward : public core::Planner {
public:
  FastDownward();

  std::optional<std::vector<std::shared_ptr<core::Action>>> solve(const std::filesystem::path &domain_file, const std::filesystem::path &problem_file);

private:
  std::string binary_path_;
  std::string result_;
};

} // namespace tampl::planner
