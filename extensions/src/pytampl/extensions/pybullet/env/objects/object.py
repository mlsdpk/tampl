import os

from importlib.resources import files
from typing import List

MODEL_FILES = files("pytampl.extensions.pybullet.env.objects.models")


class Object:
    def __init__(
        self,
        urdf_path: str,
        position: List[float] = [0, 0, 0],
        orientation: List[float] = [0, 0, 0],
        fixed_base: bool = True,
    ):
        self.urdf_path = urdf_path
        self.position = position
        self.orientation = orientation
        self.fixed_base = fixed_base
