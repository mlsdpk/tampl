#pragma once

#include <iostream>
#include <string>

#include <pybind11/embed.h>

#include "tampl/core/environment.hpp"

namespace tampl::environment {

namespace py = pybind11;

class PyEnvironment : public EnvironmentInterface {
public:
  PyEnvironment(const std::string &module_name, const std::string &cls_name,
                const py::dict &params);

  void reset() override;

  std::string get_pddl_domain_file() override;
  std::string get_pddl_problem_file() override;

private:
  py::object env_;
};

} // namespace tampl::environment
