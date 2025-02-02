#include "tampl/core/domain.hpp"

namespace tampl::core
{

Domain::Domain(const std::string& file) : pddl_file_{file} {}

bool Domain::register_action(const std::string& id, std::function<void()> callback)
{
  action_callbacks_[id] = callback;
  return true;
}

}
