#include "tampl/pddl/domain.hpp"
#include "tampl/pddl/problem.hpp"
#include "pytampl/typedefs.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(pddl, m) {
  using domain_class_t = tampl::pddl::Domain;
  py::class_<domain_class_t>(m, "Domain")
      .def(py::init<const std::string &>())
      .def("get_file_path", &domain_class_t::get_file_path);

  using problem_class_t = tampl::pddl::Problem;
  py::class_<problem_class_t>(m, "Problem")
      .def(py::init<const std::string &>())
      .def("get_file_path", &problem_class_t::get_file_path);
}

} // namespace tampl::pytampl