#include "pytampl/typedefs.hpp"
#include "tampl/agent/ompl_agent.hpp"
#include "tampl/core/agent.hpp"

namespace tampl::pytampl {

PYBIND11_MODULE(agent, m) {
  // base agent class
  using base_agent_t = tampl::core::Agent;
  py::class_<base_agent_t, std::shared_ptr<base_agent_t>>(m, "Agent")
      .def(py::init<const std::string &>());

  //////////////////////////////////////////////////////////

  // ompl specific agent class
  using ompl_agent_t = tampl::agent::OMPLAgent;
  py::class_<ompl_agent_t, base_agent_t, std::shared_ptr<ompl_agent_t>>(
      m, "OMPLAgent")
      .def(py::init<
               const std::string &,
               const std::shared_ptr<tampl::core::state_space::StateSpace> &>(),
           py::arg("id"), py::arg("state_space"))
      .def("set_state_validity_fn", &ompl_agent_t::set_state_validity_fn)
      .def("get_state_space", &ompl_agent_t::get_state_space)
      .def("get_random_state", &ompl_agent_t::get_random_state)
      .def("set_start_and_goal_states",
           &ompl_agent_t::set_start_and_goal_states);
}

} // namespace tampl::pytampl