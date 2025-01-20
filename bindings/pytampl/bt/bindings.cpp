#include "pytampl/typedefs.hpp"
#include "tampl/bt/planner_bt_engine.hpp"
#include "tampl/environment/environment_manager.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(bt, m) {
  using class_t = tampl::bt::PlannerBTEngine;

  py::class_<class_t>(m, "PlannerBTEngine")
      .def(py::init<const std::string &,
                    const std::shared_ptr<environment::EnvironmentManager> &>(),
           py::arg("bt_xml_path"), py::arg("env_manager"))
      .def("init", &class_t::init)
      .def("solve", &class_t::solve)
      .def("execute", &class_t::execute)
      .def("get_plan", &class_t::get_plan);
}

} // namespace tampl::pytampl