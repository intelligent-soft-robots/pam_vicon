************
Installation
************

Dependencies
============

This package depends on a number of third-party libraries (some of us and some
third party), see the ``find_package``-section in ``CMakeLists.txt``.

We provide an Apptainer_ image ("pam_base") which contains all required
third-party dependencies, so you don't need to install everything on your
computer. See pam_singularity_.

Our internal dependencies are best provided by setting up a workspace using
treep_ (see below).


Build
=====

We recommend using treep_ to setup a workspace to build this package:

To install treep:

.. code-block:: bash

    pip install treep

Create workspace:

.. code-block:: bash

    mkdir ~/my_workspace
    cd ~/my_workspace
    git clone https://github.com/intelligent-soft-robots/treep_isr.git
    treep --clone-https PAM_VICON  # clones packages to ./workspace/src

Build with Apptainer:

.. code-block:: bash

    cd ~/my_workspace/workspace/
    apptainer shell -e path/to/container.sif
    Apptainer> colcon build

If you don't want to use Apptainer, simply call ``colcon build`` directly.  In this case,
you need to install all dependencies locally (see
:doc:`pam_documentation:A1_overview_and_installation`).


.. _Apptainer: https://apptainer.org
.. _pam_singularity: https://github.com/intelligent-soft-robots/pam_singularity
.. _treep: https://pypi.org/project/treep/
