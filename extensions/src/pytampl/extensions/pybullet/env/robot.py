from collections import namedtuple

import pybullet

JointInfo = namedtuple(
    "JointInfo",
    [
        "jointIndex",
        "jointName",
        "jointType",
        "qIndex",
        "uIndex",
        "flags",
        "jointDamping",
        "jointFriction",
        "jointLowerLimit",
        "jointUpperLimit",
        "jointMaxForce",
        "jointMaxVelocity",
        "linkName",
        "jointAxis",
        "parentFramePos",
        "parentFrameOrn",
        "parentIndex",
    ],
)

def get_joint_info(bodyUniqueId, jointIndex, physicsClientId):
    return  JointInfo(
        *pybullet.getJointInfo(
            bodyUniqueId=bodyUniqueId,
            jointIndex=jointIndex,
            physicsClientId=physicsClientId,
        )
    )

class Robot:
    def __init__(self, id, client_id=0):
        self.id = id
        self.client_id = client_id

        # get total joints count
        n = pybullet.getNumJoints(id, physicsClientId=client_id)

        self._moveable_joint_indices = []
        for i in range(n):
            info = get_joint_info(
                id, i, physicsClientId=client_id
            )
            if info.jointType != pybullet.JOINT_FIXED:
                self._moveable_joint_indices.append(i)

    @property
    def num_actuated_joints(self):
        return len(self._moveable_joint_indices)

    def reset_joint_configuration(self, q):
        for idx, angle in zip(self._moveable_joint_indices, q):
            pybullet.resetJointState(
                self.id, idx, angle, physicsClientId=self.client_id)