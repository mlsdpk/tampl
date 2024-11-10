"""
Example script to show case motion planning in pybullet environments through TAMPL's Python Bindings
"""

from typing import List

from pytampl.core import Action
from pytampl.extensions.pybullet.env import PyBulletEnv
from pytampl.planner.ompl import OMPL


# initialize tampl PyBullet environment
env = PyBulletEnv("FrankaEmptyWorld")

# create ompl geometric motion planner
planner = OMPL("RRTConnect")

# solve the motion planning problem
if planner.solve(env):
    plan: List[Action] = planner.get_solution()
    env.render()
