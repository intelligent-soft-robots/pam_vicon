"""Interface for the PAM Vicon system."""
from ._pam_vicon import PamVicon, NoFrameDataError, get_table_pose


__all__ = ("PamVicon", "NoFrameDataError", "get_table_pose")
