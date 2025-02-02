#pragma once

#include <filesystem>
#include <string>

namespace tampl::core
{

/**
 * @class Problem
 * @brief Represents a specific planning problem instance, defining initial and goal states.
 */
class Problem
{
public:
  /**
   * @brief Constructs a problem with the given PDDL file path.
   * @param file Path to the PDDL problem file.
   */
  explicit Problem(const std::string& file);

  /**
   * @brief Gets the PDDL file path associated with this problem.
   * @return The file path as a std::filesystem::path object.
   */
  [[nodiscard]] std::filesystem::path get_file_path() const { return pddl_file_; }

private:
  std::filesystem::path pddl_file_;  ///< Path to the PDDL problem file.
};

} // namespace tampl::core
