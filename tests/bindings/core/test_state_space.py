import pytest

from pytampl.core.state_space import Type, StateSpace, RealStateSpace

# =====================================================================
# Section: Enum Testing (Type Enum)
# =====================================================================
def test_type_enum():
    """Test that the Type enum has the correct values."""
    assert Type.Rn.value == 0
    assert Type.SE2.value == 1
    assert Type.SE3.value == 2


# =====================================================================
# Section: Base StateSpace Class Testing
# =====================================================================
def test_state_space_initialization():
    """Test the initialization of the StateSpace class."""
    bounds = [(0.0, 1.0), (-1.0, 1.0)]
    ss = StateSpace(Type.Rn, 2, bounds)
    
    assert ss.type == Type.Rn
    assert ss.dimensions == 2
    assert ss.bounds == bounds
    

def test_state_space_no_bounds():
    """Test StateSpace initialization without bounds."""
    ss = StateSpace(Type.SE2, 2)
    
    assert ss.type == Type.SE2
    assert ss.dimensions == 2
    assert ss.bounds == []  # No bounds provided, should be empty


# =====================================================================
# Section: StateSpace Subtypes Testing (Real, SE2, SE3)
# =====================================================================
def test_real_initialization():
    """Test the Real subclass initialization."""
    bounds = [(0.0, 1.0), (0.0, 1.0)]
    real_space = RealStateSpace(2, bounds)
    
    assert real_space.type == Type.Rn
    assert real_space.dimensions == 2
    assert real_space.bounds == bounds

def test_real_no_bounds():
    """Test Real initialization without bounds."""
    real_space = RealStateSpace(3)
    
    assert real_space.type == Type.Rn
    assert real_space.dimensions == 3
    assert real_space.bounds == []  # Default bounds

def test_bounds_are_stored_correctly():
    """Check that bounds are correctly stored for various inputs."""
    bounds = [(-10.0, 10.0), (5.0, 15.0), (-5.0, 5.0)]
    ss = StateSpace(Type.Rn, 3, bounds)
    
    assert ss.bounds == bounds  # Bounds should match exactly

    # Verify bounds in Real
    real_space = RealStateSpace(3, bounds)
    assert real_space.bounds == bounds