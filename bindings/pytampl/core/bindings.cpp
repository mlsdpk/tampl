#include "pytampl/typedefs.hpp"
#include "tampl/core/action.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(core, m) {
  using class_t = tampl::core::Action;
  py::class_<class_t>(m, "Action")
      .def(py::init<>())
      .def_property("type", &class_t::get_type, &class_t::set_type)
      .def_property("parameters", &class_t::get_parameters,
                    &class_t::set_parameters);
}

} // namespace tampl::pytampl