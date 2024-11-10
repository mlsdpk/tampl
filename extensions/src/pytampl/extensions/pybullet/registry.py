class Registry:
    _registry = {}

    @classmethod
    def register(cls, name, scene_cls, object_classes):
        cls._registry[name] = (scene_cls, object_classes)

    @classmethod
    def is_registered(cls, name):
        return name in cls._registry

    @classmethod
    def get_env(cls, name):
        if not cls.is_registered(name):
            raise ValueError(f"Environment '{name}' is not registered.")
        scene_cls, object_classes = cls._registry[name]
        scene = scene_cls()
        objects = [obj_cls() for obj_cls in object_classes]
        return scene, objects