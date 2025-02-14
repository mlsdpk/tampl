# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- New fast downward planner
- Integrate fast downward to BT TaskPlanner
- C++ examples to showcase task planning with BT
- Python bindings support
- Minimal logging functionality (wrapper around fmt)

### Changed
- Tidy up CMake files
    - use CPM to handle dependenices
    - use PackageProject to handle installtion part
- Improve BT engine default plugins loading part
    - make use of build and install directories through cmake

### Deprecated

### Removed
- FastForward planner is no longer supported
- Remove all the enviornment (simulation) related stuffs
    - tampl extensions (pddlgym, pybullet etc)

### Fixed
