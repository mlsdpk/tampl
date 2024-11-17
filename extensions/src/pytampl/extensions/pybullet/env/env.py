import os
import time

from typing import List

import pybullet
import pybullet_data

from pytampl.agent import OMPLAgent
from pytampl.core.state import State, Real
from pytampl.core.state_space import Type, RealStateSpace
from pytampl.environment import Environment
from .robot import Robot
from ..registry import Registry


class PyBulletEnv(Environment):
    def __init__(self, env_name: str):

        # check whether given env exists or not
        if not Registry.is_registered(env_name):
            raise ValueError(f"The environment '{env_name}' is not registered.")

        # get the scene and objects from env
        self._scene, self._objects = Registry.get_env(env_name)

        # setup pybullet environment

        # main simulation server, with a GUI
        self.gui_id = pybullet.connect(pybullet.GUI)

        # simulation server only used for collision detection
        self.col_id = pybullet.connect(pybullet.DIRECT)

        # add bodies to both of the environments
        self.robots, _ = self.__load_environment(self.gui_id, self._scene, self._objects)
        self.col_robot, col_obstacles = self.__load_environment(self.col_id, self._scene, self._objects)

        # get joint states
        # q, v= self.col_robot[0].get_joint_states()
        # print("col_robot[0].get_joint_states: ", q)

        ###########################################################

        # SETUP OMPL AGENTS

        self._agents = []

        # TODO: get state space from env:object
        # get all lower and upper bounds of all the joints
        # for now assume we only have one object
        bounds = self.__get_state_bounds(self.robots[0].id, self.col_id)

        # we only support real state space for now
        ss = RealStateSpace(len(bounds), bounds)

        # TODO: get agent id from env:object
        agent = OMPLAgent(id="franka", state_space=ss)
        agent.set_state_validity_fn(self.is_state_valid)
        self._agents.append(agent)

        ###########################################################

        super().__init__(env_name)

    @property
    def agents(self):
        return self._agents
    
    def sample_state(self, agent, n_retries=100):
        count = 0
        while count <= n_retries:
            state = agent.get_random_state()
            if self.is_state_valid(state):
                return state
            count += 1
        return None

    def reset(self):
        ## TEMPORARY: set start and goal states

        for agent in self._agents:
            start_goal_pair = []
            while len(start_goal_pair) < 2:
                temp_state = agent.get_random_state()
                if self.is_state_valid(temp_state):
                    start_goal_pair.append(temp_state)
            self.robots[0].reset_joint_configuration([start_goal_pair[0][i] for i in range(len(start_goal_pair[0]))])
            agent.set_start_and_goal_states(start_goal_pair[0], start_goal_pair[1])

    def _is_not_fixed(self, joint_idx):
        joint_info = pybullet.getJointInfo(self.obj_ids[0], joint_idx)
        print("joint_info: ", joint_info)
        return joint_info[2] != pybullet.JOINT_FIXED

    def is_state_valid(self, state: State):

        # convert state to q
        # q = [state[i] for i in range(len(state))]
        # print("q: ", q)

        # self.col_robot[0].reset_joint_configuration(q)
        # if self.collision_checker.in_collision():
        #     print("in collision")
        #     return False

        return True
    
    def __set_state(self, q, client_id):
        for i in range(self.robots[0].num_actuated_joints):
            pybullet.resetJointState(self.robots[0].id, i, q[i], targetVelocity=0, physicsClientId=client_id)

    def render(self, plan):
        print(plan)
        start_state = plan[0].get_from_state()
        for q in plan:
            curr_state = plan[0].get_to_state()
            q = [curr_state[i] for i in range(len(curr_state))]
            self.__set_state(q, self.gui_id)
            pybullet.stepSimulation(physicsClientId=self.gui_id)
            time.sleep(0.01)
            
    def __load_obj(
        self,
        obj,
        client_id
    ):
        return pybullet.loadURDF(
                obj.urdf_path,
                obj.position,
                pybullet.getQuaternionFromEuler(obj.orientation),
                useFixedBase=obj.fixed_base,
                physicsClientId=client_id,
            )

    # TODO: move this into robot class
    def __get_state_bounds(self, obj_id, client_id):
        bounds = []

        idx = {}
        idx["jointName"] = 1
        idx["jointType"] = 2
        idx["jointLowerLimit"] = 8
        idx["jointUpperLimit"] = 9

        # go through each joint in the object
        for i in range(pybullet.getNumJoints(obj_id)):
            joint_info = pybullet.getJointInfo(obj_id, i, physicsClientId=client_id)
            q, _, _, _ = pybullet.getJointState(obj_id, i, physicsClientId=client_id)

            # only supports revolute joint for now
            if joint_info[idx["jointType"]] != pybullet.JOINT_FIXED:
                print(f"joint name: {joint_info[idx["jointName"]]}, lower: {joint_info[idx["jointLowerLimit"]]}, upper: {joint_info[idx["jointUpperLimit"]]} q: ", q)
                bounds.append((joint_info[idx["jointLowerLimit"]], joint_info[idx["jointUpperLimit"]]))

        return bounds
    
    def __load_environment(self, client_id, scene, objects):
        pybullet.setGravity(0, 0, -9.8, physicsClientId=client_id)
        pybullet.setTimeStep(1.0 / 240.0, physicsClientId=client_id)
        pybullet.setAdditionalSearchPath(pybullet_data.getDataPath(), physicsClientId=client_id)

        # load the scene
        scene.load()
        obstacles = []

        # ground plane
        ground_id = pybullet.loadURDF(
            "plane.urdf", [0, 0, 0], useFixedBase=True, physicsClientId=client_id
        )
        obstacles.append(ground_id)

        # load all the objects
        robots = [Robot(self.__load_obj(obj=obj, client_id=client_id), client_id=client_id) for obj in objects]
        return robots, obstacles
    
    def __create_col_pairs(self, robot, obstacles):
        pairs = []
        for link_name in robot.link_names:
            link = (robot.uid, link_name)
            for obstacle in obstacles:
                pairs.append((link, obstacle))

        # Print the result
        print(pairs)
        return pairs