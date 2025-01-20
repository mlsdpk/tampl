#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <unordered_map>

#ifdef TAMPL_BUILD_PYBINDINGS
#include "pybind11/embed.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#endif

#include "tampl/core/environment.hpp"
#include "tampl/environment/environment_factory.hpp"
#include "tampl/pddl/domain.hpp"
#include "tampl/pddl/problem.hpp"

namespace tampl::environment {

class EnvironmentManager {
public:
  explicit EnvironmentManager(const std::string &config_file);
  void init(const std::string &env_name);
  void reset();

  std::shared_ptr<pddl::Domain> get_domain();
  std::shared_ptr<pddl::Problem> get_problem();
  bool has_action(const std::string &id);
  bool execute(const std::string &id);

private:
#ifdef TAMPL_BUILD_PYBINDINGS
  /// @brief instance for handling python interpreter
  /// We use optional to make sure the interpreter is not activated
  /// if the class is executed from python side
  std::optional<pybind11::scoped_interpreter> interpreter_guard_;
#endif

  /// @brief store user-defined environment instance
  std::unique_ptr<EnvironmentInterface> environment_;

  std::shared_ptr<pddl::Domain> domain_;
  std::shared_ptr<pddl::Problem> problem_;
};

} // namespace tampl::environment