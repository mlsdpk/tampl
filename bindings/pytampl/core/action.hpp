#pragma once

#include "pytampl/typedefs.hpp"
#include "tampl/core/action.hpp"

namespace tampl::pytampl {

class PyAction : public core::Action {
public:
  /* Inherit the constructors */
  using Action::Action;

  /* Trampoline (need one for each virtual function) */
  bool on_init() override {
    PYBIND11_OVERRIDE(
        bool,    /* Return type */
        Action,  /* Parent class */
        on_init, /* Name of function in C++ (must match Python name) */
    );
  }

  /* Trampoline (need one for each virtual function) */
  bool on_activate() override {
    PYBIND11_OVERRIDE(
        bool,        /* Return type */
        Action,      /* Parent class */
        on_activate, /* Name of function in C++ (must match Python name) */
    );
  }

  /* Trampoline (need one for each virtual function) */
  bool on_execute() override {
    PYBIND11_OVERRIDE(
        bool,       /* Return type */
        Action,     /* Parent class */
        on_execute, /* Name of function in C++ (must match Python name) */
    );
  }

  /* Trampoline (need one for each virtual function) */
  bool on_deactivate() override {
    PYBIND11_OVERRIDE(
        bool,          /* Return type */
        Action,        /* Parent class */
        on_deactivate, /* Name of function in C++ (must match Python name) */
    );
  }

  /* Trampoline (need one for each virtual function) */
  bool on_shutdown() override {
    PYBIND11_OVERRIDE(
        bool,        /* Return type */
        Action,      /* Parent class */
        on_shutdown, /* Name of function in C++ (must match Python name) */
    );
  }
};

} // namespace tampl::pytampl