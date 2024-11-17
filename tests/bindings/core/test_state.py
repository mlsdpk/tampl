import pytest

from pytampl.core.state import Real
from pytampl.core.state_space import Type

# Test case for state space type
def test_state_space_type():
    dims = 5 # arbitary
    real_state = Real(dims)
    assert real_state.type == Type.Rn

# Test case for initializing with different dimensions
@pytest.mark.parametrize("dims", [0, 5, 1000, 1000000])
def test_real_initialization(dims):
    """Test that the Real state initializes with the correct size and default values."""
    real_state = Real(dims)

    # Check that the values vector has the correct size
    assert len(real_state) == dims, f"Expected {dims} elements, but got {len(real_state)}."

    # Check that all elements are initialized to 0.0
    for i in range(min(dims, 10)):  # Check the first 10 elements to avoid large data checks
        assert real_state[i] == 0.0, f"Expected 0.0, but got {real_state[i]}."

# Test case for reading and writing the 'values' attribute
def test_real_values_read_write():
    """Test that the 'values' vector can be read and written correctly."""
    dims = 5
    real_state = Real(dims)

    # Check the initial values
    initial_values = [real_state[i] for i in range(len(real_state))]
    assert initial_values == [0.0] * dims, f"Expected all values to be 0.0, but got {initial_values}"

    # Modify the values
    for i in range(len(real_state)):
        real_state[i] = float(i + 1)

    # Check the modified values
    current_values = [real_state[i] for i in range(len(real_state))]
    expected_values = [float(i + 1) for i in range(dims)]
    assert current_values == expected_values, f"Expected {expected_values}, but got {current_values}"