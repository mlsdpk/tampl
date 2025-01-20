import pytest

from pytampl.core.action import Action

# Test case for setting and getting action ID
def test_action_id():
    action = Action("random_id")
    assert action.id == "random_id"

    # change id
    action.id = "another_id"
    assert action.id == "another_id"