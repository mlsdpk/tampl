#include "tampl/planner/fast_forward/fast_forward.hpp"

namespace tampl::planner {

FastForward::FastForward() {
  // Check the environment variable first
  const char *ff_binary = std::getenv("FF_PLANNER_BINARY_PATH");
  if (ff_binary && std::filesystem::exists(ff_binary)) {
    binary_path_ = std::string(ff_binary);
  } else {
    // Try the install location
    if (std::filesystem::exists(FF_PLANNER_EXECUTABLE_INSTALL)) {
      binary_path_ = FF_PLANNER_EXECUTABLE_INSTALL;
    }
    // Fallback to the build directory
    else if (std::filesystem::exists(FF_PLANNER_EXECUTABLE_BUILD)) {
      binary_path_ = FF_PLANNER_EXECUTABLE_BUILD;
    }
  }

  if (!binary_path_.empty()) {
    printf("FF Planner binary found at %s", FF_PLANNER_EXECUTABLE_INSTALL);
  } else {
    throw std::runtime_error("FF binary not found. Please set "
                             "FF_PLANNER_BINARY_PATH environment variable.");
  }
}

} // namespace tampl::planner
