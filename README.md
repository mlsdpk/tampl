# Task and Motion Planning Library (TAMPL)

> **⚠ Warning:** This library is still under development.

An all-in-one library for prototyping, benchmarking, and integrating task and motion planning algorithms into real-world systems, all powered by behavior trees.

## Building Instructions

### Prerequisites

Before building TAMPL from source, ensure that the necessary dependencies are installed.

**For Linux (Ubuntu/Debian)**
```bash
$ sudo apt install -y libboost-all-dev libeigen3-dev libzmq3-dev libsqlite3-dev
```

**For macOS (using Homebrew)**
```bash
$ brew install boost eigen zeromq sqlite
```

TAMPL also uses [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) to manage additional dependenices such as [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP), [OMPL](https://github.com/ompl/ompl), and more. These dependencies can be found in [dependencies.cmake](cmake/dependencies.cmake). 

### Building from Source

> Note: If you want to build TAMPL with Python bindings, you can skip this section and proceed to [Python Bindings (Experimental)](#python-bindings-experimental)

Run the following commands from the repository's top-level directory to build TAMPL from source. The first build may take some time as all necessary dependencies will be downloaded and compiled.

```bash
$ mkdir build && cd build
$ cmake ..
$ make -j$(nproc)
```

### Python Bindings (Experimental)

TAMPL also supports experimental Python bindings. To enable this, first set up a Python virtual environment and install the necessary dependencies:

```bash
$ python -m venv tampl_venv
$ source tampl_venv/bin/activate
$ pip install -r requirements.txt
```

Then, run the following command from the repository's top-level directory to build TAMPL along with its Python bindings from source:
```bash
$ pip install -v .
```

## Running Examples

All the examples demonstrating TAMPL's capabilities can be found in the [examples](examples/).
