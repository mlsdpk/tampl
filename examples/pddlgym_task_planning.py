from typing import List

from pytampl.core import Action
from pytampl.extensions.pddlgym import PDDLGymEnv
from pytampl.pddl import Domain, Problem
from pytampl.planner import FastForward

# initialize tampl PDDLGym environment
env = PDDLGymEnv("PDDLEnvHanoi-v0")

# create task planner
# available planners (Fast Forward, Fast Downward, STRIPS)
# https://github.com/aibasel/pyperplan (STRIPS)
planner = FastForward()

# solve the task planning problem
if planner.solve(Domain(env.domain), Problem(env.problem)):
    plan: List[Action] = planner.get_solution()
    for i, action in enumerate(plan):
        print(f"{i}: {action.type} ({' '.join(action.parameters)})")
else:
    print("Solution not found!")