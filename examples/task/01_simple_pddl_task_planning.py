import os

from typing import List

from pytampl.bt import PlannerBTEngine
from pytampl.core import Action, Domain, Problem

# create domain and problem instances from pddl files
domain = Domain(file=os.path.join(os.path.dirname(__file__), "pddl/lets_eat/domain.pddl")
problem = Problem(file=os.path.join(os.path.dirname(__file__), "pddl/lets_eat/problem.pddl")

# we need to make sure each action in the domain has associated executors
def action_pick_up_callback():
    print("Executing action 'pick-up')


def action_drop_callback():
    print("Executing action 'drop')


def action_move_callback():
    print("Executing action 'move')


# each action id must be the same as the ones described in the domain file
domain.register_action('pick-up', action_pick_up_callback)
domain.register_action('drop', action_drop_callback)
domain.register_action('move', action_move_callback)

# create planner BT engine
bt_xml_path = os.path.join(os.path.dirname(__file__), "../../behavior_trees/task/simple_task_planner.xml")
engine = PlannerBTEngine(bt_xml_path=bt_xml_path, domain=domain, problem=problem)

# run the planner (this will only find a solution plan 
# and do not execute each registered action callbacks)
solved = engine.solve()

if solved:
    # get the solution
    plan: List[Action] = engine.get_plan()

    # execute the solution plan
    engine.execute(plan)
else:
    print("Solution not found!")
