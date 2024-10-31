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
    printf("FF Planner binary found at %s\n", FF_PLANNER_EXECUTABLE_INSTALL);
  } else {
    throw std::runtime_error("FF binary not found. Please set "
                             "FF_PLANNER_BINARY_PATH environment variable.");
  }
}

bool FastForward::solve(const std::shared_ptr<core::Environment> &env) {
  // cast env into pddl-specific environment (ff requires this)
  auto pddl_env = std::dynamic_pointer_cast<environment::PDDLEnvironment>(env);
  if (!pddl_env) {
    std::cerr
        << "Failed to cast the input env to environment::PDDLEnvironment. Make "
           "sure you are passing an instance of environment::PDDLEnvironment "
           "type\n";
    return false; // Handle the failure case appropriately
  }

  std::ostringstream cmd_stream;
  cmd_stream << "gtimeout"
             << " " << 10 << " " << FF_PLANNER_EXECUTABLE_INSTALL << " -o "
             << pddl_env->pddl_domain().get_file_path() << " -f "
             << pddl_env->pddl_problem().get_file_path();
  const std::string cmd_str = cmd_stream.str();

  // open a pipe to execute the command and read the output
  std::array<char, 128> buffer;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd_str.c_str(), "r"),
                                                pclose);

  if (!pipe) {
    std::cerr << "Failed to open pipe!" << std::endl;
    return false;
  }

  // Read the command output
  result_.clear();
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result_ += buffer.data();
  }

  // convert the FF specific output to tampl specific
  plan_.clear();
  conversions::from_ff_result(result_, plan_);

  return true;
}

} // namespace tampl::planner
