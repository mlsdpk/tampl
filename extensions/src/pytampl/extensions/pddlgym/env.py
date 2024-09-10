import pytampl
import pddlgym

class PDDLGymEnv(pytampl.environment.Environment):
    def __init__(self):
        pytampl.environment.Environment.__init__(self, PDDLGymEnv)