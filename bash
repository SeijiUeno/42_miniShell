#!/bin/bash

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

# Check if c_formatter_42 is installed
if ! command -v c_formatter_42 &> /dev/null; then
    echo -e "${RED}Error: c_formatter_42 is not installed. Please install it first.${RESET}"
    exit 1
fi

# Check for directory argument
TARGET_DIR="${1:-.}"

if [ ! -d "$TARGET_DIR" ]; then
    echo -e "${RED}Error: Specified directory does not exist: ${TARGET_DIR}${RESET}"
    exit 1
fi

# Find and format all .c and .h files in the specified directory
echo -e "${GREEN}Formatting all .c and .h files in the directory: ${TARGET_DIR}...${RESET}"

find "$TARGET_DIR" -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    echo -e "Formatting: ${file}"
    
    # Format file and overwrite the original
    c_formatter_42 < "$file" > "$file.formatted" && mv "$file.formatted" "$file"
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Formatted: ${file}${RESET}"
    else
        echo -e "${RED}Failed to format: ${file}${RESET}"
    fi
done

echo -e "${GREEN}All files have been formatted and updated in: ${TARGET_DIR}!${RESET}"
