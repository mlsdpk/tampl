# Task and Motion Planning Library (TAMPL)

## Build instructions for development (temporary)

### setup
```
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

## Issues
- [ ] Example python script cannot find dylib at runtime. Manually setting is still required at the moment as: `export DYLD_LIBRARY_PATH=<path-to-dylib>:$DYLD_LIBRARY_PATH`
- [ ] Fix FF planner build failure on Unix