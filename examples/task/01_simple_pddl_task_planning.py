'''
  This example demonstrates a simple task planning setup using PDDL.
  It showcases how to load a domain and problem, and use the Fast Downward planner
  to generate a solution plan.
'''

import os

from pytampl.bt import PlannerBTEngine
from pytampl.core import Domain, Problem
from pytampl.planner import FastDownward

# Step 1: Create domain and problem instances from PDDL files
domain = Domain(file=os.path.join(os.path.dirname(__file__), "../data/pddl/task/lets_eat/domain.pddl"))
problem = Problem(file=os.path.join(os.path.dirname(__file__), "../data/pddl/task/lets_eat/problem.pddl"))

# Step 2: Create a Fast Downward task planner
# This planner will attempt to generate a valid plan based on the given domain and problem.
task_planner = FastDownward()

# Step 3: Solve the task planning problem
# If a solution is found, it will contain a sequence of actions to achieve the goal.
solution = task_planner.solve(domain.get_file_path(), problem.get_file_path());

if solution:
    print(f"Task planner found a solution plan with {len(solution)} actions")
    for i in range(len(solution)):
        print(f"[{i}] action id: {solution[i].id}")
else:
    print("Solution not found")
