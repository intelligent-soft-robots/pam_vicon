Software related to the ISR-PAM Vicon system.

``pam_vicon`` mainly implements an o80 interface for the Vicon system in the ISR
table tennis lab based on the generic interface from
:doc:`vicon_transformer <vicon_transformer:index>`.


Overview
========

o80 Driver/Standalone
---------------------

``pam_vicon`` provides implementations of the :ref:`vicon_transformer o80 Driver
and Standalone <vicon_transformer:overview_o80>` that are configured for the
objects in the ISR table tennis lab:

- :cpp:class:`~pam_vicon::o80Driver`
- :cpp:class:`~pam_vicon::o80Standalone`

Python bindings are provided in :mod:`pam_vicon.o80`.
For a usage example see :ref:`example_o80_client`.

If you want to modify Vicon objects, see :ref:`configure_subjects_o80`.


Calibrate Transformation between Tennicam and Vicon
---------------------------------------------------

The two executables ``record_tennicam_vicon_trajectory`` and
``compute_tennicam_to_vicon_transform`` can be used to find the transformation
between tennicam and Vicon by recording synchronised position data with both
systems (using a ball attached to the "LED stick").

The process is described in detail in the :ref:`general PAM documentation
<pam_documentation:tennicam_vicon_transform>`.



.. toctree::
   :caption: General Documentation
   :maxdepth: 1

   doc/install.rst
   doc/examples.rst
   doc/configure_o80_driver_subjects.rst
