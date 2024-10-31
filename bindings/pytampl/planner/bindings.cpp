#include "pytampl/typedefs.hpp"
#include "tampl/planner/fast_forward/fast_forward.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(planner, m) {
  using class_t = tampl::planner::FastForward;
  using base_class_t = tampl::core::Planner;

  py::class_<base_class_t>(m, "Planner")
      .def("get_solution", &class_t::get_solution);

  py::class_<class_t, base_class_t>(m, "FastForward")
      .def(py::init<>())
      .def("solve", &class_t::solve);
}

} // namespace tampl::pytampl