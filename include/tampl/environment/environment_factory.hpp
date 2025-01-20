#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

#include "tampl/core/environment.hpp"
#include "tampl/environment/cpp_environment.hpp"

#ifdef TAMPL_BUILD_PYBINDINGS
#include "tampl/environment/py_environment.hpp"
#endif

namespace tampl::environment {

#ifdef TAMPL_BUILD_PYBINDINGS
inline py::object convert_yaml_to_pyobject(const YAML::Node &node) {
  // handle scalar values (string, int, float, bool)
  if (node.IsScalar()) {
    if (node.Tag() == "tag:yaml.org,2002:int") {
      return py::int_(node.as<int>());
    } else if (node.Tag() == "tag:yaml.org,2002:float") {
      return py::float_(node.as<double>());
    } else if (node.Tag() == "tag:yaml.org,2002:bool") {
      return py::bool_(node.as<bool>());
    } else {
      return py::str(node.as<std::string>());
    }
  }
  // handle sequences (e.g., lists)
  else if (node.IsSequence()) {
    py::list py_list;
    for (const auto &element : node) {
      py_list.append(convert_yaml_to_pyobject(element));
    }
    return py_list;
  }
  // handle maps (e.g., dictionaries)
  else if (node.IsMap()) {
    py::dict py_dict;
    for (const auto &kv : node) {
      py_dict[py::str(kv.first.as<std::string>())] =
          convert_yaml_to_pyobject(kv.second);
    }
    return py_dict;
  } else {
    throw std::runtime_error("Unsupported YAML node type.");
  }
}
#endif

class EnvironmentFactory {
public:
  // Load the YAML configuration and register environments
  static void register_environments(const std::string &config_file);

  // Create the environment based on the name
  static std::unique_ptr<EnvironmentInterface>
  create(const std::string &env_name);

private:
  using env_register_factory_t =
      std::function<std::unique_ptr<EnvironmentInterface>()>;
  using env_registry_t =
      std::unordered_map<std::string, env_register_factory_t>;
  static inline env_registry_t env_registry;
};

} // namespace tampl::environment