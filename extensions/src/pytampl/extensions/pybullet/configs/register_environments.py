from ..registry import Registry
from ..env.objects import Franka
from ..env.scenes import EmptyWorld

# Register all environment configurations
# Syntax: Registry.register(<name>, scene, [objects])
Registry.register("FrankaEmptyWorld", EmptyWorld, [Franka])
