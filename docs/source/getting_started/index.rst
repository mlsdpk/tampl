.. _getting_started:

Getting Started
===============

This document will walk you through setting up TAMPL on your machine and running your first example to get started with task and motion planning.

.. warning::

  This library is currently under development, and the following build instructions might not work seamlessly. If you encounter any issues during the build or installation process, please reach out to the maintainers for assistance.

Installation
************

Building from source
####################

1. Clone the repository

  .. code-block:: bash

    git clone --recursive https://github.com/mlsdpk/tampl.git

2. Set up virtual environment

  .. code-block:: bash

    cd tampl && python3 -m venv tampl_venv
    source tampl_venv/bin/activate

3. Install dependencies

  .. code-block:: bash

    pip install -r requirements.txt


4. Build and install TAMPL

  Install the core library (this will install both C++ library and its Python bindings):

  .. warning::

    The build process may take some time depending on your machine's performance, as it involves compiling the C++ library and its submodules. We are actively working on eliminating the need to build dependencies in the upcoming release.

  .. code-block:: bash

    pip install . --config-settings=build.tool-args=-j8

  Install extensions (optional):

  .. code-block:: bash

    cd extensions && pip install .

5. Verifying installation

  Run the following command in the terminal to verify whether the library was installed successfully or not:

  .. code-block:: bash

    python -c "import pytampl; print('TAMPL installed successfully!')"

---

Running Your First Example
**************************