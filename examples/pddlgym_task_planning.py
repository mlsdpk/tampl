from pytampl.extensions.pddlgym import PDDLGymEnv
from pytampl.planner import FastForward

# initialize tampl PDDLGym environment
env = PDDLGymEnv("PDDLEnvSlidetile-v0")

# create task planner 
# available planners (Fast Forward, Fast Downward, STRIPS)
# https://github.com/aibasel/pyperplan (STRIPS)
planner = FastForward()