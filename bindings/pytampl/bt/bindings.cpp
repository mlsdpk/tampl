#include "pytampl/typedefs.hpp"
#include "tampl/bt/behavior_trees/config.hpp"
#include "tampl/bt/planner_bt_engine.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(bt, m) {
  using class_t = tampl::bt::PlannerBTEngine;

  py::class_<class_t>(m, "PlannerBTEngine")
      .def(py::init<const std::string &,
                    const std::shared_ptr<core::Domain> &,
                    const std::shared_ptr<core::Problem>>(),
           py::arg("bt_xml_path"), py::arg("domain"), py::arg("problem"))
      .def("init", &class_t::init)
      .def("solve", &class_t::solve)
      .def("execute", &class_t::execute)
      .def("get_plan", &class_t::get_plan);

  ////////////////////////////////////////////////////////////////////////

  m.def("default_behavior_trees_dir", &tampl::bt::default_behavior_trees_dir);
}

} // namespace tampl::pytampl
