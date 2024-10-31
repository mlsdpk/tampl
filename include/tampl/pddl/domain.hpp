#pragma once

#include <string>

namespace tampl::pddl {
class Domain {
public:
  explicit Domain(const std::string &pddl_file_path)
      : pddl_file_path_{pddl_file_path} {}

  const std::string &get_file_path() const { return pddl_file_path_; }

private:
  std::string pddl_file_path_{};
};
} // namespace tampl::pddl