#!/bin/bash

# If no command is provided, start a bash shell
if [[ $# -eq 0 ]]; then
    exec bash
else
    # Execute the provided command
    exec "$@"
fi