#include "tampl/planner/fast_downward/fast_downward.hpp"

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

bool FastDownward::solve() {
  return true;
}

} // namespace tampl::planner
