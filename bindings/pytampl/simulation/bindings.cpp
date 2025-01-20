#include "pytampl/typedefs.hpp"
#include "tampl/simulation/simulator.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(simulation, m) {
  // simulator class
  using simulator_t = tampl::simulation::Simulator;
  py::class_<simulator_t, std::shared_ptr<simulator_t>>(m, "Simulator")
      .def(py::init<const std::string &>())
      .def("init", &simulator_t::init)
      .def("reset", &simulator_t::reset);
}

} // namespace tampl::pytampl