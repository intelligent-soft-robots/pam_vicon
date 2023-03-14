# SPDX-License-Identifier: BSD-3-Clause

"""Use o80 front end to get the pose of the robot base from Vicon.

The back end is expected to be run in a separate process (e.g. by
``vicon_o80_standalone``) using the same segment ID.  It needs to be started before
initialising the front end.
"""
import contextlib
import signal_handler
from spatial_transformation import Transformation
from pam_vicon.o80 import FrontEnd, Subjects


def main() -> None:
    SEGMENT_ID = "vicon"
    frontend = FrontEnd(SEGMENT_ID)
    frontend.reset_next_index()

    signal_handler.init()  # for detecting ctrl+c
    with contextlib.suppress(KeyboardInterrupt, SystemExit):
        while not signal_handler.has_received_sigint():
            obs = frontend.wait_for_next()
            vicon_frame = obs.get_extended_state()

            robot_base = vicon_frame.subjects[Subjects.MUSCLE_BASE]

            # convert pose to native Python class (makes it more convenient to use).
            robot_pose = Transformation.from_cpp(robot_base.global_pose)

            print(f"Robot Base Pose: {robot_pose}")


if __name__ == "__main__":
    main()
