#include "tampl/planner/fast_downward/fast_downward.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace tampl::planner {

FastDownward::FastDownward() {
  // Check the environment variable first
  const char *fd_binary = std::getenv("FD_PLANNER_BINARY_PATH");
  if (fd_binary && std::filesystem::exists(fd_binary)) {
    binary_path_ = std::string(fd_binary);
  } else {
    // Try the install location
    if (std::filesystem::exists(FD_PLANNER_EXECUTABLE_INSTALL)) {
       binary_path_ = FD_PLANNER_EXECUTABLE_INSTALL;
    }
    // Fallback to the build directory
    else if (std::filesystem::exists(FD_PLANNER_EXECUTABLE_BUILD)) {
       binary_path_ = FD_PLANNER_EXECUTABLE_BUILD;
    }
  }

  if (!binary_path_.empty()) {
    TAMPL_DEBUG("FD Planner binary found at {}", binary_path_);
  } else {
    throw std::runtime_error("FD binary not found. Please set "
                             "FD_PLANNER_BINARY_PATH environment variable.");
  }
}

std::optional<std::vector<std::shared_ptr<core::Action>>> FastDownward::solve(
  const std::filesystem::path &domain_file,
  const std::filesystem::path &problem_file) {

  std::ostringstream cmd_stream;
  cmd_stream << binary_path_ << " "
             << domain_file.string() << " "
             << problem_file.string() << " "
             << "--search 'astar(lmcut())'"; // hardcoded for now
  const std::string& cmd_str = cmd_stream.str();

  TAMPL_DEBUG("[FastDownward] Executing cmd: {}", cmd_str);
  system(cmd_str.c_str());

  // this will generate plan as a file so we have to read it
  // might not be the final approach but for now we'll stick with this

  std::vector<std::shared_ptr<core::Action>> task_plan;
  if (!conversions::from_fd_sas_plan("sas_plan", task_plan))
  {
    return std::nullopt;
  }

  return task_plan;
}

std::vector<std::string> parseSASPlan(const std::string &filename) {
    std::vector<std::string> actions;
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return actions;
    }

    while (std::getline(file, line)) {
        // Ignore empty lines and cost line (lines starting with ";")
        if (line.empty() || line[0] == ';') {
            continue;
        }

        std::istringstream iss(line);
        std::string action;
        iss >> action; // Read first word (action name)

        if (!action.empty()) {
            actions.push_back(action);
        }
    }

    return actions;
}

} // namespace tampl::planner
