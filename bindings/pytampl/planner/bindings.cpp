#include "pytampl/typedefs.hpp"
// #include "tampl/planner/fast_forward/fast_forward.hpp"
#include "tampl/planner/ompl/ompl.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(planner, m) {
//   using class_t = tampl::planner::FastForward;
  using base_class_t = tampl::core::Planner;

  py::class_<base_class_t>(m, "Planner")
      .def("get_solution", &base_class_t::get_solution);

  ///////////////////////////////////////////////////////////////////

  // TODO(Phone): move this under task specific submodule
//   py::class_<class_t, base_class_t>(m, "FastForward")
//       .def(py::init<>())
//       .def("solve", &class_t::solve);

  ///////////////////////////////////////////////////////////////////

  // OMPL submodule
  using ompl_planner_t = tampl::planner::ompl::OMPL;
  auto m_ompl = m.def_submodule("ompl", "TAMPL's python bindings for OMPL");

  py::class_<ompl_planner_t, base_class_t>(m_ompl, "OMPL")
      .def(py::init<const std::string &>())
      .def("solve", &ompl_planner_t::solve, py::arg("agent"), py::arg("goal"));
}

} // namespace tampl::pytampl