#pragma once

#include <vector>

namespace tampl::core {

namespace state_space {

enum class Type { Rn, SE2, SE3 };

class StateSpace {
public:
  Type type;
  size_t dimensions;

  /// @brief each pair represents min and max bounds for a dimension
  std::vector<std::pair<double, double>> bounds;

  StateSpace(const Type t, const size_t dims,
             const std::vector<std::pair<double, double>> &bounds = {})
      : type(t), dimensions(dims), bounds(std::move(bounds)) {}

  virtual ~StateSpace() = default;
};

class RealStateSpace : public StateSpace {
public:
  RealStateSpace(const size_t dims,
                 const std::vector<std::pair<double, double>> &bounds = {})
      : StateSpace(Type::Rn, dims, std::move(bounds)) {}
};

} // namespace state_space

namespace state {

class State {
public:
  State(const state_space::Type t) : type(t) {}
  virtual ~State() = default;
  state_space::Type type;
};

class Real : public State {
public:
  Real(const size_t dims) : values(dims, 0.0), State(state_space::Type::Rn) {}
  double operator[](size_t i) const { return values[i]; }
  double &operator[](size_t i) { return values[i]; }
  size_t size() const { return values.size(); }

private:
  std::vector<double> values;
};

} // namespace state

} // namespace tampl::core