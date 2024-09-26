#!/bin/bash

# Clean previous builds
make fclean

# Compile the test program
make test_tokenizer

# Check if compilation was successful
if [ ! -f test_tokenizer ]; then
    echo "Compilation failed."
    exit 1
fi

# Run the test program and capture the output
./test_tokenizer > test_output.txt

# Display the output
cat test_output.txt

# Optionally, compare the output with expected results
# For now, we'll just display the captured output
