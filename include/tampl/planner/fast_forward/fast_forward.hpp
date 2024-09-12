#include "tampl/interface/planner.hpp"

#include <filesystem>

namespace tampl::planner {

class FastForward : public Planner {
public:
  FastForward();

private:
  std::string binary_path_;
};

} // namespace tampl::planner