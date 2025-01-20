#include "tampl/environment/environment_factory.hpp"

namespace tampl::environment {

// TODO(Phone):
// 3) how to support new C++ env which is built outside of tampl
// Load the YAML configuration and register environments
void EnvironmentFactory::register_environments(const std::string &config_file) {
  YAML::Node config = YAML::LoadFile(config_file);

  printf("Registering enviornments from %s\n", config_file.c_str());

  if (config["environments"]) {
    // iterate through each environment name in the list
    for (const auto &env : config["environments"]) {

      // get environment name
      const auto &env_name = env.as<std::string>();

      // get the type of environment
      const auto &type = config[env_name]["type"].as<std::string>();

      printf("env: %s, type: %s\n", env_name.c_str(), type.c_str());

      if (type == "cpp") {
        env_registry[env_name] = [env_name]() {
          return std::make_unique<CppEnvironment>(env_name);
        };
      }
#ifdef TAMPL_BUILD_PYBINDINGS
      else if (type == "python") {
        // if it's a Python environment, pass module and class names
        const auto &module_name = config[env_name]["module"].as<std::string>();
        const auto &class_name = config[env_name]["class"].as<std::string>();

        // extract environment specific params as a python dictionary
        const auto &params_node = config[env_name]["params"];
        py::dict params;
        for (const auto &kv : params_node) {
          params[py::str(kv.first.as<std::string>())] =
              convert_yaml_to_pyobject(kv.second);
        }

        env_registry[env_name] = [module_name, class_name, params]() {
          return std::make_unique<PyEnvironment>(module_name, class_name,
                                                 params);
        };
      }
#endif
      else {
        std::cerr << "Unknown environment type: " << type << std::endl;
      }
    }
  }
}

// Create the environment based on the name
std::unique_ptr<EnvironmentInterface>
EnvironmentFactory::create(const std::string &env_name) {
  if (env_registry.find(env_name) != env_registry.end()) {
    return env_registry[env_name]();
  }

  throw std::runtime_error("Unknown environment: " + env_name);
}

} // namespace tampl::environment