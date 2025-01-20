#include "tampl/environment/py_environment.hpp"

namespace tampl::environment {

PyEnvironment::PyEnvironment(const std::string &module_name,
                             const std::string &cls_name,
                             const py::dict &params) {
  std::cout << "PyEnvironment::PyEnvironment(): " << module_name << ", "
            << cls_name << std::endl;

  // dynamically import the Python module and create the class instance
  auto py_module = py::module_::import(module_name.c_str());
  env_ = py_module.attr(cls_name.c_str())(**params);
}

void PyEnvironment::reset() {
  std::cout << "PyEnvironment::reset()\n";
  env_.attr("reset")();
}

// TODO: consider changing this to std::file_system::path
std::string PyEnvironment::get_pddl_domain_file() {
  std::cout << "PyEnvironment::get_pddl_domain_file()\n";
  return env_.attr("get_pddl_domain_file")().cast<std::string>();
}

// TODO: consider changing this to std::file_system::path
std::string PyEnvironment::get_pddl_problem_file() {
  std::cout << "PyEnvironment::get_pddl_problem_file()\n";
  return env_.attr("get_pddl_problem_file")().cast<std::string>();
}

} // namespace tampl::environment