#include "pytampl/typedefs.hpp"
#include "tampl/planner/fast_forward/fast_forward.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(planner, m) {
  using class_t = tampl::planner::FastForward;
  py::class_<class_t>(m, "FastForward").def(py::init<>());
}

} // namespace tampl::pytampl