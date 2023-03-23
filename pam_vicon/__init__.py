"""Interface for the PAM Vicon system."""
from ._pam_vicon import PamVicon, NoFrameDataError, get_table_pose


DEFAULT_ORIGIN_SUBJECT = "Pamy_ceiling"
"""Name of the default origin subject in the table tennis lab.

This value should be used as default where ever the origin subject can be specified.
Update here, if the name of the origin subject used in the lab changes.
"""


__all__ = ("PamVicon", "NoFrameDataError", "get_table_pose", "DEFAULT_ORIGIN_SUBJECT")
