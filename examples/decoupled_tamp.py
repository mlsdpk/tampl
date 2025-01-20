"""
This example shows the usage of behavior trees to perform 
the task planning in PDDLGym environment.
"""

from typing import List

from pytampl.bt import PlannerBTEngine
from pytampl.core import Action
from pytampl.extensions.pddlgym import PDDLGymEnv


# initialize tampl PDDLGym environment
env = PDDLGymEnv("PDDLEnvHanoi-v0")

# get pddl domain and problem files
pddl_domain_file = env.domain.get_file_path()
pddl_problem_file = env.problem.get_file_path()
print(f"Using PDDL domain from {pddl_domain_file}")
print(f"Using PDDL problem from {pddl_problem_file}")

# Create planner engine from task planning behavior tree
engine = PlannerBTEngine(
    bt_xml_path="/Users/phone/Documents/projects/tampl/examples/behavior_trees/task/task_planner.xml"
)

# Pass pddl domain and problem files to engine
engine.initialize(
    {
        "domain": pddl_domain_file,
        "problem": pddl_problem_file,
    }
)

# Run the planner
solved = engine.run()

# here comes the interesting part
# To execute the solution plan, you can simply attach callbacks
# in engine for each action in the pddl domain then engine will internally
# executes each action properly with its own generated behavior tree
def action_callback(act: Action):
    env.step(act)
engine.execute_plan(action_callback=action_callback)
