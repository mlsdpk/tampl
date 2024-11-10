from abc import ABC, abstractmethod


class Scene(ABC):
    @abstractmethod
    def load(self):
        pass
