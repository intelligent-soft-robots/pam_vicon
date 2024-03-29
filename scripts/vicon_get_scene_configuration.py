#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-3-Clause
"""
Get data from Vicon server and print poses of robot, table and ball machine in JSON
format.
"""
import argparse
import contextlib
import functools
import json
import logging
import pathlib
import sys
import typing as t

import numpy as np

from spatial_transformation import Transformation
from vicon_transformer import (
    PlaybackReceiver,
    ViconReceiverConfig,
    ViconReceiver,
    ViconTransformer,
)

import pam_vicon
from pam_vicon.o80 import Subjects, get_subject_names

if t.TYPE_CHECKING:
    from vicon_transformer.vicon_transformer_bindings import Receiver

_subject_names = get_subject_names()

ROBOT_BASE_SUBJECT = _subject_names[Subjects.ROBOT1_BASE]
BALL_MACHINE_SUBJECT = _subject_names[Subjects.BALL_LAUNCHER_FRONT]
TABLE_CORNER_SUBJECTS = (
    _subject_names[Subjects.TABLE_CORNER_1],
    _subject_names[Subjects.TABLE_CORNER_2],
    _subject_names[Subjects.TABLE_CORNER_3],
    _subject_names[Subjects.TABLE_CORNER_4],
)


class JsonEncoder(json.JSONEncoder):
    """JSON encoder that handles custom types used here"""

    @functools.singledispatchmethod
    def default(self, obj):  # noqa[ANN]
        return super().default(obj)

    @default.register
    def _(self, obj: np.ndarray) -> t.Any:
        return obj.tolist()

    @default.register
    def _(self, obj: Transformation) -> t.Any:
        return {
            "position": obj.translation,
            "orientation": obj.rotation.as_quat(),
        }


def get_table_transform(transformer: ViconTransformer) -> Transformation:
    """Get pose of the table based on poses of the corner markers."""
    corner_poses_world = [
        transformer.get_transform(name) for name in TABLE_CORNER_SUBJECTS
    ]
    corner_positions_world = [c.translation for c in corner_poses_world]

    return pam_vicon.get_table_pose(corner_positions_world)


def main() -> int:
    # parse arguments
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "host_or_file",
        type=str,
        help="Hostname of Vicon server or path to recorded file.",
    )
    parser.add_argument(
        "--origin-subject",
        "-o",
        type=str,
        default=pam_vicon.DEFAULT_ORIGIN_SUBJECT,
        help="Name of the origin marker (used as origin for the world frame).",
    )
    args = parser.parse_args()

    logging.basicConfig(level=logging.INFO)

    receiver: Receiver
    if (filename := pathlib.Path(args.host_or_file)).is_file():
        receiver = PlaybackReceiver(filename)
    else:
        config = ViconReceiverConfig()
        receiver = ViconReceiver(args.host_or_file, config)
        receiver.connect()

    transformer = ViconTransformer(receiver, args.origin_subject)
    transformer.wait_for_origin_subject_data()

    transformer.update()

    output = {
        "robot": transformer.get_transform(ROBOT_BASE_SUBJECT),
        "ball_machine": transformer.get_transform(BALL_MACHINE_SUBJECT),
        "table": get_table_transform(transformer),
    }

    print(json.dumps(output, indent=4, cls=JsonEncoder))

    return 0


if __name__ == "__main__":
    with contextlib.suppress(KeyboardInterrupt):
        sys.exit(main())
