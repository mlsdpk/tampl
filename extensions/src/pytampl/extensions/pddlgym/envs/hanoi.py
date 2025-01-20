from pytampl.core.action import Action

class Move(Action):
    def __init__(self):
        print("Move.__init__() called")
        super().__init__()

    # def on_init(self):
    #     return True
    
    # def on_activate(self):
    #     # TODO(Phone): update this method
    #     return True
    
    # def on_deactivate(self):
    #     return True
    
    # def on_shutdown(self):
    #     return True