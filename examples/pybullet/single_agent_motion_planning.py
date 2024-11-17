"""
Example script to show case motion planning in pybullet environments through TAMPL's Python Bindings
"""

from typing import List

from pytampl.core import Action
from pytampl.extensions.pybullet.env import PyBulletEnv
from pytampl.planner.ompl import OMPL

# initialize tampl PyBullet environment
env = PyBulletEnv("FrankaEmptyWorld")
env.reset()

# get the controllable agent from the env
# only one agent in this env
agent = env.agents[0]

# generate a random goal for the agent
goal = env.sample_state(agent)

# create ompl geometric motion planner
planner = OMPL("RRTConnect")

# solve the motion planning problem
if planner.solve(agent=agent, goal=goal):
    plan: List[Action] = planner.get_solution()
    env.render(plan)
