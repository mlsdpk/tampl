import pytampl
import pddlgym

class PDDLGymEnv(pytampl.environment.Environment):
    def __init__(self, env_name: str):
        pytampl.environment.Environment.__init__(self, env_name)

        # create ppdlgym env
        self.env = pddlgym.make(env_name)

        # info includes problem and domain files
        # Note: there can be many problem files and reset randomly selects one
        self.state, info = self.env.reset()
        self.problem = info['problem_file']
        self.domain = info['domain_file']