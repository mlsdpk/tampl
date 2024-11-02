# Task and Motion Planning Library (TAMPL)

## Build instructions for development (temporary)

### setup
```
$ git clone --recursive https://github.com/mlsdpk/tampl.git
$ python -m venv tampl_venv
$ source tampl_venv/bin/activate
$ pip install -r requirements.txt
```

### build and install tampl
```
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=<path-to-install> ..
$ make
```

### build and install pytampl
```
$ pip install .
```

### build and install pytampl-extensions
```
$ cd extensions && pip install .
```

## Use Cases / Examples

### Task Planning in PDDLGym

You can use TAMPL’s Python bindings to perform task planning directly within [PDDLGym](https://github.com/tomsilver/pddlgym/) environments. The provided example script demonstrates how to solve tasks in a PDDLGym environment and generate a visual solution as a GIF. Simply modify the script to adjust the environment settings as needed. 

To run the example:

```bash
$ python examples/pddlgym_task_planning.py
```

<img src="docs/img/PDDLEnvHanoi-v0.output.gif" width="200" alt="">
<p align="left">
  <img src="docs/img/PDDLEnvSlidetile-v0.output.gif" width="200" alt="">
  <img src="docs/img/PDDLEnvMaze-v0.output.gif" width="200" alt="">
  <img src="docs/img/PDDLEnvBlocks-v0.output.gif" width="200" alt="">
</p>



## Issues
- [ ] Example python script cannot find dylib at runtime. Manually setting is still required at the moment as: `export DYLD_LIBRARY_PATH=<path-to-dylib>:$DYLD_LIBRARY_PATH`
- [ ] Fix FF planner build failure on Unix
