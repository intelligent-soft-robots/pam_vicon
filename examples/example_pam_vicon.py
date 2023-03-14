# SPDX-License-Identifier: BSD-3-Clause

"""Use PamVicon to access robot and table pose.

An o80 back end is expected to be run in a separate process (e.g. by
``vicon_o80_standalone``) using the same segment ID.  It needs to be started before
initialising PamVicon.
"""
from pam_vicon import PamVicon


def main() -> None:
    SEGMENT_ID = "vicon"
    pv = PamVicon(SEGMENT_ID)

    # update with latest Vicon data provided through o80
    pv.update()

    robot_pose = pv.get_robot_pose()
    table_pose = pv.get_table_pose(yaw_only=True)

    print(f"Robot Base Pose: {robot_pose}")
    print(f"Table Pose: {table_pose}")


if __name__ == "__main__":
    main()
