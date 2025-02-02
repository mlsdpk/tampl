#pragma once

#include <functional>
#include <string>

namespace tampl::core
{

class Problem
{
public:
  explicit Problem(const std::string& file);

protected:
  std::string pddl_file_;
};

}
