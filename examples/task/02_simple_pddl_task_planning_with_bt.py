import os

from typing import List

from pytampl.bt import PlannerBTEngine
from pytampl.core import Action

# absolute paths to domain and problem file
domain_file = os.path.join(os.path.dirname(__file__), "pddl/lets_eat/domain.pddl")
problem_file = os.path.join(os.path.dirname(__file__), "pddl/lets_eat/problem.pddl")

# Create planner engine from task planning behavior tree
bt_xml_path = os.path.join(os.path.dirname(__file__), "behavior_trees/task_planning.xml")
engine = PlannerBTEngine(
    bt_xml_path=bt_xml_path, domain_file=domain_file, problem_file=problem_file
)

# Run the planner
solved = engine.run()
if solved:
    plan: List[Action] = engine.get_plan()
    print("======== Plan ========")
    for i, action in enumerate(plan):
        print(f"{i}: {action.type} ({' '.join(action.parameters)})")
else:
    print("Solution not found!")
