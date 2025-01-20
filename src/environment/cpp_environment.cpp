#include "tampl/environment/cpp_environment.hpp"

namespace tampl::environment {

CppEnvironment::CppEnvironment(const std::string &env_name) {
  std::cout << "CppEnvironment::CppEnvironment(): " << env_name << std::endl;
}

void CppEnvironment::reset() { std::cout << "CppEnvironment::reset()\n"; }

} // namespace tampl::environment