import imageio
from typing import List
import pddlgym
from pddlgym.parser import parse_plan_step
from pytampl.environment import PDDLEnvironment
from pytampl.core import Action


class PDDLGymEnv(PDDLEnvironment):
    def __init__(self, env_name: str):
        # create ppdlgym env
        self.env = pddlgym.make(env_name)
        self.env_name = env_name

        # info includes problem and domain files
        # Note: there can be many problem files and reset randomly selects one
        self.state, info = self.env.reset()

        PDDLEnvironment.__init__(
            self, env_name, info["domain_file"], info["problem_file"]
        )

    def render(self, solution: List[Action]):
        act_predicates = [
            self.env.domain.predicates[a] for a in list(self.env.domain.actions)
        ]
        plan = [
            parse_plan_step(
                action.type + " " + " ".join(action.parameters),
                self.env.domain.operators.values(),
                act_predicates,
                self.state.objects,
                operators_as_actions=self.env.domain.operators_as_actions,
            )
            for action in solution
        ]

        images = []
        images.append(self.env.render())
        for act in plan:
            obs, reward, done, _, _ = self.env.step(act)
            images.append(self.env.render())
            if done:
                break
        self.env.close()

        # Save as a GIF
        output_path = f"{self.env_name}.output.gif"
        imageio.mimsave(output_path, images, format="GIF", fps=3)
        print(f"GIF saved at {output_path}")
