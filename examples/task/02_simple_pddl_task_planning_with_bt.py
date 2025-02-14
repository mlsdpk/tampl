'''
  This example demonstrates how to use Behavior Trees (BT) with PDDL in TAMPL for simple task planning.
  The PDDL (Planning Domain Definition Language) files define the available actions and the problem context,
  while the BT engine handles planning and execution in a structured manner.
'''

import os

from pytampl.bt import default_behavior_trees_dir, PlannerBTEngine
from pytampl.core import Domain, Problem
from pytampl.planner import FastDownward

# Step 1: Create domain and problem instances from PDDL files
domain = Domain(file=os.path.join(os.path.dirname(__file__), "../data/pddl/task/lets_eat/domain.pddl"))
problem = Problem(file=os.path.join(os.path.dirname(__file__), "../data/pddl/task/lets_eat/problem.pddl"))

# Step 2: Register action executors
# Each action in the domain must be associated with a corresponding function (executor)
# that will be called when the planner executes the action.
domain.register_action("pick-up", lambda: print("Executing action 'pick-up'"))
domain.register_action("drop", lambda: print("Executing action 'drop'"))
domain.register_action("move", lambda: print("Executing action 'move'"))

# Step 3: Create the Behavior Tree (BT) planner engine
# The BT engine will load the simple task planning behavior tree XML file
# from the default set of behavior tree based planners
bt_xml_path = os.path.join(default_behavior_trees_dir(), "task/simple_task_planner.xml")
print(f"BT XML PATH: {bt_xml_path}")
engine = PlannerBTEngine(bt_xml_path, domain, problem)

# Step 4: Initialize the planner BT engine
# This sets up internal structures and prepares the planner for execution.
engine.init();

# Step 5: Solve the task planning problem
# This step generates a valid plan if a solution exists, but does not execute it yet.
solved = engine.solve();

if solved:
    # Step 6: Retrieve the generated plan
    plan = engine.get_plan()

    # Step 7: Execute the solution plan
    # Each action in the plan will be executed in order, triggering the registered callbacks.
    engine.execute(plan)
else:
    # if no solution is found, inform the user.
    print("Solution not found")
