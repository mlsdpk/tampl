#pragma once

#include <functional>
#include <string>

namespace tampl::core
{

class Domain
{
public:
  explicit Domain(const std::string& file);

  bool register_action(const std::string& id, std::function<void()> callback);

protected:
  std::string pddl_file_;

  std::unordered_map<std::string, std::function<void()>> action_callbacks_;
};

}

