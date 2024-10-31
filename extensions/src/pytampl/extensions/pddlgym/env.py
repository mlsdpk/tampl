import pytampl
import pddlgym


class PDDLGymEnv(pytampl.environment.PDDLEnvironment):
    def __init__(self, env_name: str):
        # create ppdlgym env
        env = pddlgym.make(env_name)

        # info includes problem and domain files
        # Note: there can be many problem files and reset randomly selects one
        state, info = env.reset()

        pytampl.environment.PDDLEnvironment.__init__(
            self, env_name, info["domain_file"], info["problem_file"]
        )
