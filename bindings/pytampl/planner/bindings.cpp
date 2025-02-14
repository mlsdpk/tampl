#include "pytampl/typedefs.hpp"
#include "tampl/planner/fast_downward/fast_downward.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(planner, m) {
  using base_class_t = tampl::core::Planner;

  py::class_<base_class_t, std::shared_ptr<base_class_t>>(m, "Planner")
      .def("get_solution", &base_class_t::get_solution);

  ///////////////////////////////////////////////////////////////////

  // TODO(Phone): move this under task specific submodule
  using fd_planner_t = tampl::planner::FastDownward;
  py::class_<fd_planner_t, base_class_t, std::shared_ptr<fd_planner_t>>(m, "FastDownward")
    .def(py::init<>())
    .def("solve", &fd_planner_t::solve, py::arg("domain_file"), py::arg("problem_file"));

  ///////////////////////////////////////////////////////////////////

}

} // namespace tampl::pytampl
