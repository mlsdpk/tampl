from abc import ABC, abstractmethod

class PyEnvironment(ABC):
    @abstractmethod
    def __init__(self, **kwargs):
        """
        Abstract constructor that enforces derived classes to accept keyword arguments.
        """
        pass

    @abstractmethod
    def reset(self):
        pass

    @abstractmethod
    def get_pddl_domain_file(self) -> str :
        pass

    @abstractmethod
    def get_pddl_problem_file(self) -> str :
        pass