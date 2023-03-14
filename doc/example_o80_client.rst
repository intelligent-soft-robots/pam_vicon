.. _example_o80_client:

***************************************
Examples: Access Vicon Data Through o80
***************************************

.. note::

   All examples on this page requires an o80 back end to be running.  This is done by
   executing ``vicon_o80_standalone`` in a separate terminal before running the example.


The example ``o80_get_robot_pose.py`` shows a minimal example on how to use the o80
front end to get the pose of the robot base from Vicon:

.. literalinclude:: /PKG/examples/o80_get_robot_pose.py


The script ``vicon_o80_print_data.py`` shows a slightly more complex example, printing
all subject data and using :cpp:func:`~pam_vicon::get_subject_names` to get the name of
each subject:

.. literalinclude:: /PKG/scripts/vicon_o80_print_data.py
