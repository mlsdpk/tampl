#include "pytampl/typedefs.hpp"
#include "tampl/environment/environment_manager.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(environment, m) {
  // base environment class
  //   using base_env_t = tampl::core::Environment;
  //   py::class_<base_env_t, std::shared_ptr<base_env_t>>(m, "Environment")
  //       .def(py::init<const std::string &>());

  // environment manager class
  using env_manager_t = tampl::environment::EnvironmentManager;
  py::class_<env_manager_t, std::shared_ptr<env_manager_t>>(
      m, "EnvironmentManager")
      .def(py::init<const std::string &>(), py::arg("config_file"))
      .def("init", &env_manager_t::init)
      .def("reset", &env_manager_t::reset);

  //////////////////////////////////////////////////////////

  // pddl specific enviornment class
  //   using pddl_env_t = tampl::environment::PDDLEnvironment;
  //   py::class_<pddl_env_t, base_env_t, std::shared_ptr<pddl_env_t>>(
  //       m, "PDDLEnvironment")
  //       .def(py::init<const std::string &, const std::string &,
  //                     const std::string &>())
  //       .def_property("domain",
  //                     (pddl::Domain & (pddl_env_t::*)()) &
  //                         pddl_env_t::pddl_domain, // Getter
  //                     nullptr)                     // No setter
  //       .def_property("problem",
  //                     (pddl::Problem & (pddl_env_t::*)()) &
  //                         pddl_env_t::pddl_problem, // Getter
  //                     nullptr);                     // No setter

  //////////////////////////////////////////////////////////
}

} // namespace tampl::pytampl