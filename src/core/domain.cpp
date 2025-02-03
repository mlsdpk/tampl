#include "tampl/core/domain.hpp"

namespace tampl::core
{

Domain::Domain(const std::string& file) : pddl_file_{std::filesystem::path{file}} {}

bool Domain::register_action(const std::string& id, std::function<void()> callback)
{
  if (action_callbacks_.find(id) != action_callbacks_.end())
  {
    return false;
  }

  action_callbacks_.emplace(id, std::move(callback));
  return true;
}

bool Domain::execute(const std::string& id)
{
  auto itr = action_callbacks_.find(id);
  if (itr == action_callbacks_.end())
    return false;

  // TODO: this will be blocking
  // use the success, failure output from the callback to determine the execution return
  itr->second.operator()();
  return true;
}

}
