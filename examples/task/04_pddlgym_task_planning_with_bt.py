import os

from typing import List

from pytampl.bt import BEHAVIOR_TREES_DIR, PlannerBTEngine
from pytampl.core.action import Action
from pytampl.environment import EnvironmentManager

# path to environments config file
env_cfg_path = "config/environments.yaml"

# create environment instance
env_manager = EnvironmentManager(env_cfg_path)

# TODO: may be no need init and reset
env_manager.init("tower_of_hanoi")
env_manager.reset()

# create planner engine
# make this BEHAVIOR_TREES_DIR variable work
bt_xml_path = os.path.join(BEHAVIOR_TREES_DIR, "task/simple_task_planner.xml")
engine = PlannerBTEngine(bt_xml_path=bt_xml_path, env_manager=env_manager)

# TODO: do we have to init?
engine.init()

# run the planner
solved = engine.solve()
# if solved:
#     # get the solution
#     plan: List[Action] = engine.get_plan()

#     # execute the solution plan
#     engine.execute(plan)
# else:
#     print("Solution not found!")
