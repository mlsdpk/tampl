#include "pytampl/typedefs.hpp"
#include "tampl/bt/planner_bt_engine.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(bt, m) {
  using class_t = tampl::bt::PlannerBTEngine;

  py::class_<class_t>(m, "PlannerBTEngine")
      .def(py::init<const std::string &, const std::string &,
                    const std::string &>(),
           py::arg("bt_xml_path"), py::arg("domain_file"),
           py::arg("problem_file"))
      .def("run", &class_t::run)
      .def("get_plan", &class_t::get_plan);
}

} // namespace tampl::pytampl