import os
import time

from typing import List

import pybullet
import pybullet_data

from pytampl.environment import OMPLEnvironment
from ..registry import Registry


class PyBulletEnv(OMPLEnvironment):
    def __init__(self, env_name: str):

        # check whether given env exists or not
        if not Registry.is_registered(env_name):
            raise ValueError(f"The environment '{env_name}' is not registered.")

        # get the scene and objects from env
        self._scene, self._objects = Registry.get_env(env_name)

        # setup pybullet environment
        pybullet.connect(pybullet.GUI)
        pybullet.setGravity(0, 0, -9.8)
        pybullet.setTimeStep(1.0 / 240.0)
        pybullet.setAdditionalSearchPath(pybullet_data.getDataPath())
        pybullet.loadURDF("plane.urdf")

        # load the scene
        self._scene.load()

        # load all the objects
        for obj in self._objects:
            self.__load_obj(obj)

        # initialize OMPL env
        OMPLEnvironment.__init__(self, env_name)

    def render(self):
        while True:
            pybullet.stepSimulation()

    def __load_obj(
        self,
        obj,
    ):
        pybullet.loadURDF(
            obj.urdf_path,
            obj.position,
            pybullet.getQuaternionFromEuler(obj.orientation),
            useFixedBase=obj.fixed_base,
        )
