#!/bin/bash

# Check if the required number of arguments is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 <argument>"
    exit 1
fi

# Compile the C program
make

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Run the compiled program with the provided argument(s)
./arger-hu "$@"
