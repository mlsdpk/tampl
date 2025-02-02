# Task and Motion Planning Library (TAMPL)

> **⚠ Warning:** This library is still under development.

An all-in-one library for prototyping, benchmarking, and integrating task and motion planning algorithms into real-world systems, all powered by behavior trees.

## Building Instructions

TAMPL uses [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) to manage all the required dependenices. These dependencies can be foundd in [dependencies.cmake](cmake/dependencies.cmake). 

Run the following commands from the repository's top-level directory to build TAMPL from source. The first build may take some time as all necessary dependencies will be downloaded and compiled.

```bash
$ mkdir build && cd build
$ cmake ..
$ make -j$(nproc)
```
