from typing import List
from pytampl.environment import OMPLEnvironment


class PyBulletEnv(OMPLEnvironment):
    def __init__(self, env_name: str):
        OMPLEnvironment.__init__(self, env_name)
