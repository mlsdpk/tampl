import os

from typing import List

from pytampl.core import Action
from pytampl.planner import FastForward

# absolute paths to domain and problem file
domain_file = os.path.join(os.path.dirname(__file__), "pddl/lets_eat/domain.pddl")
problem_file = os.path.join(os.path.dirname(__file__), "pddl/lets_eat/problem.pddl")

# create task planner
# available planners (Fast Forward, Fast Downward)
planner = FastForward()

# solve the task planning problem
if planner.solve(domain_file, problem_file):
    plan: List[Action] = planner.get_solution()
    print("======== Plan ========")
    for i, action in enumerate(plan):
        print(f"{i}: {action.type} ({' '.join(action.parameters)})")
else:
    print("Solution not found!")
