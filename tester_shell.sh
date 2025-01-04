#!/bin/bash

# Set Valgrind options
VALGRIND="valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=valgrind.supp"
EXECUTABLE=./minishell

# Function to run a command and log output
test_command() {
  local desc="$1"
  local cmd="$2"
  echo "Test: $desc"
  echo "$cmd" | $VALGRIND $EXECUTABLE
  echo "---------------------------------------"
}

# Test Cases

echo "Starting Valgrind Tests for Minishell"

# Basic Commands
test_command "Echo Command" "echo Hello World"
test_command "List Directory" "ls -l"
test_command "Print Working Directory" "pwd"

# Built-in Commands
test_command "Change Directory" "cd /tmp && pwd"
test_command "Export Variable" "export TEST=123 && echo $TEST"
test_command "Unset Variable" "unset TEST && echo $TEST"
test_command "Print Environment" "env"

test_command "Invalid Command" "invalid_command"
test_command "Permission Denied Command" "/bin/ls-invalid"
test_command "Directory as Command" "/etc"

# Redirection and Pipes
test_command "Output Redirection" "echo Hello > test.txt"
test_command "Input Redirection" "cat < test.txt"
test_command "Pipes" "echo Hello | grep H"
test_command "Combined Redirection and Pipe" "cat < test.txt | grep H > output.txt"

# Heredoc
test_command "Heredoc Test" "cat << EOF
Hello
EOF"

# Environment Variable Expansion
test_command "Variable Expansion" "export VAR=hello && echo $VAR"
test_command "Unset Variable Expansion" "unset VAR && echo $VAR"

# Signals
echo "Running Signal Test (use Ctrl+C)..."
test_command "Sleep Command" "sleep 10"

# Large Input
test_command "Large Input" "printf 'echo %.0sA{1..10000}\n'"

# Multiple Pipes and Commands
test_command "Multiple Pipes" "ls -l | grep minishell | wc -l"
test_command "Chained Cats" "echo 'test' | cat | cat | cat | wc -l"

# Exit Test
test_command "Exit Command" "exit"

# Resource Limit Test
test_command "Resource Limit" "ulimit -n 1000"

echo "Valgrind Tests Completed"

# Valgrind Suppression File
cat << EOF > valgrind.supp
{
   ignore_libreadline_memory_errors
   Memcheck:Leak
   ...
   obj:*/libreadline.so.*
}
{
   ignore_binaries_memory_errors
   Memcheck:Leak
   ...
   obj:/usr/bin/*
}
EOF
