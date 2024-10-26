#include "pytampl/environment/environment_py.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(environment, m) {
  // environment class definition
  using class_t = tampl::environment::Environment<>;
  py::class_<class_t>(m, "Environment").def(py::init<const std::string &>());
}

} // namespace tampl::pytampl