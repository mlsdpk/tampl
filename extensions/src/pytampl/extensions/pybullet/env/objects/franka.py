from .object import Object, MODEL_FILES


class Franka(Object):
    def __init__(self, model_name="fr3", position=[0, 0, 0], orientation=[0, 0, 0]):
        super().__init__(
            urdf_path=str(MODEL_FILES / f"franka/{model_name}_franka_hand.urdf"),
            position=position,
            orientation=orientation,
            fixed_base=True,
        )
