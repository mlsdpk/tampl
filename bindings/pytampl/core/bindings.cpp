#include "pytampl/core/action.hpp"
#include "pytampl/typedefs.hpp"
#include "tampl/core/state.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(core, m) {

  //////////////////////////////////////////////////////////

  // state space related

  // state space submodule
  auto m_state_space = m.def_submodule(
      "state_space",
      "Python bindings for the namespace tampl::core::state_space.");

  // StateSpace type enum
  using state_space_enum_t = tampl::core::state_space::Type;
  py::enum_<state_space_enum_t>(m_state_space, "Type")
      .value("Rn", state_space_enum_t::Rn)
      .value("SE2", state_space_enum_t::SE2)
      .value("SE3", state_space_enum_t::SE3)
      .export_values();

  // Base state space
  using base_state_space_t = tampl::core::state_space::StateSpace;
  py::class_<base_state_space_t, std::shared_ptr<base_state_space_t>>(
      m_state_space, "StateSpace")
      .def(py::init<state_space_enum_t, std::size_t,
                    std::vector<std::pair<double, double>>>(),
           py::arg("type"), py::arg("dimensions"),
           py::arg("bounds") = std::vector<std::pair<double, double>>())
      .def_readonly("type", &base_state_space_t::type)
      .def_readonly("dimensions", &base_state_space_t::dimensions)
      .def_readonly("bounds", &base_state_space_t::bounds);

  // Real state space
  using real_state_space_t = tampl::core::state_space::RealStateSpace;
  py::class_<real_state_space_t, base_state_space_t,
             std::shared_ptr<real_state_space_t>>(m_state_space,
                                                  "RealStateSpace")
      .def(py::init<std::size_t, std::vector<std::pair<double, double>>>(),
           py::arg("dimensions"),
           py::arg("bounds") = std::vector<std::pair<double, double>>());

  //////////////////////////////////////////////////////////

  // state related

  // state submodule
  auto m_state = m.def_submodule(
      "state", "Python bindings for the namespace tampl::core::state.");

  // Base state space
  using base_state_t = tampl::core::state::State;
  py::class_<base_state_t, std::shared_ptr<base_state_t>>(m_state, "State")
      .def(py::init<state_space_enum_t>(), py::arg("type"))
      .def_readonly("type", &base_state_t::type);

  using real_state_t = tampl::core::state::Real;
  py::class_<real_state_t, base_state_t, std::shared_ptr<real_state_t>>(m_state,
                                                                        "Real")
      .def(py::init<std::size_t>(), py::arg("dims"))
      // Bind __setitem__ (non-const access)
      .def(
          "__setitem__",
          [](real_state_t &self, size_t i, double value) { self[i] = value; },
          "Set element")
      // Bind __getitem__ (const access)
      .def(
          "__getitem__",
          [](const real_state_t &self, size_t i) -> double { return self[i]; },
          "Access element (const)")
      .def("__len__", &real_state_t::size,
           "Return the length of the values vector");

  //////////////////////////////////////////////////////////

  // action related

  // action submodule
  auto m_action = m.def_submodule(
      "action", "Python bindings for the namespace tampl::core::action.");

  // Base action class
  using base_action_t = tampl::core::Action;
  using trampoline_action_t = tampl::pytampl::PyAction;
  py::class_<base_action_t, trampoline_action_t,
             std::shared_ptr<base_action_t>>(m_action, "Action")
      .def(py::init<>())
      .def(py::init<const std::string &>())
      .def(py::init<const std::shared_ptr<tampl::core::state::State> &,
                    const std::shared_ptr<tampl::core::state::State> &>())
      .def_property("id", &base_action_t::get_id, &base_action_t::set_id)
      .def_property("type", &base_action_t::get_type, &base_action_t::set_type)
      .def_property("parameters", &base_action_t::get_parameters,
                    &base_action_t::set_parameters)
      .def("get_from_state", &base_action_t::get_from_state)
      .def("get_to_state", &base_action_t::get_to_state)
      .def("on_init", &base_action_t::on_init)
      .def("on_activate", &base_action_t::on_activate)
      .def("on_execute", &base_action_t::on_execute)
      .def("on_deactivate", &base_action_t::on_deactivate)
      .def("on_shutdown", &base_action_t::on_shutdown);

  //////////////////////////////////////////////////////////
}

} // namespace tampl::pytampl