# import imageio
# from typing import List
import pddlgym
# from pddlgym.parser import parse_plan_step
# from pytampl.core import Action

from pytampl.environment import PyEnvironment

class PDDLGymEnv(PyEnvironment):
    def __init__(self, **kwargs):
        """ Initialize the environment with the given parameters. """
        self.params = kwargs
        print("Initialized PDDLGymEnv with the following parameters:")
        self.__pretty_print(self.params)

        # get unique env name
        self.env_name = self.params["env_name"]

        # create ppdlgym env
        self.env = pddlgym.make(self.env_name)

        # info includes problem and domain files
        # Note: there can be many problem files and reset randomly selects one
        self.state, self.info = self.env.reset()


    def __pretty_print(self, data, indent=0):
        """ Recursively print the dictionary in a readable format. """
        prefix = " " * indent
        if isinstance(data, dict):
            for key, value in data.items():
                print(f"{prefix}{key}:")
                self.__pretty_print(value, indent + 4)
        elif isinstance(data, list):
            for item in data:
                self.__pretty_print(item, indent + 4)
        else:
            print(f"{prefix}{data}")

    def reset(self):
        print("PDDLGymEnv.reset() called")

    def get_pddl_domain_file(self) -> str :
        print("PDDLGymEnv.get_pddl_domain_file() called")
        return self.info["domain_file"]

    def get_pddl_problem_file(self) -> str :
        return self.info["problem_file"]

    # def render(self, solution: List[Action]):
    #     act_predicates = [
    #         self.env.domain.predicates[a] for a in list(self.env.domain.actions)
    #     ]
    #     plan = [
    #         parse_plan_step(
    #             action.type + " " + " ".join(action.parameters),
    #             self.env.domain.operators.values(),
    #             act_predicates,
    #             self.state.objects,
    #             operators_as_actions=self.env.domain.operators_as_actions,
    #         )
    #         for action in solution
    #     ]

    #     images = []
    #     images.append(self.env.render())
    #     for act in plan:
    #         obs, reward, done, _, _ = self.env.step(act)
    #         images.append(self.env.render())
    #         if done:
    #             break
    #     self.env.close()

    #     # Save as a GIF
    #     output_path = f"{self.env_name}.output.gif"
    #     imageio.mimsave(output_path, images, format="GIF", fps=3)
    #     print(f"GIF saved at {output_path}")
