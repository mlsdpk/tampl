#pragma once

#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>

namespace tampl::core
{

/**
 * @class Domain
 * @brief Represents a domain, aka "physics" of the overall planning problem.
 */
class Domain
{
public:
  /**
   * @brief Constructs a domain with the given PDDL file path.
   * @param file Path to the PDDL domain file.
   */
  explicit Domain(const std::string& file);

  /**
   * @brief Registers an action with a corresponding callback function.
   * @param id Unique identifier for the action.
   * @param callback Function to be executed when the action is triggered.
   * @return True if registration is successful, false otherwise
   */
  [[nodiscard]] bool register_action(const std::string& id, std::function<void()> callback);

  /**
   * @brief Gets the PDDL file path associated with this domain.
   * @return The file path as a std::filesystem::path object.
   */
  [[nodiscard]] std::filesystem::path get_file_path() const { return pddl_file_; }

private:
  std::filesystem::path pddl_file_;  ///< Path to the PDDL domain file.
  std::unordered_map<std::string, std::function<void()>> action_callbacks_; ///< Map of action IDs to callbacks.
};

} // namespace tampl::core
