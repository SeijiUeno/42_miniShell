# Buildins for Mini-Shell Project

## Echo

### Auxiliary Function: `check_if_arg_minus_n`

**Purpose**  
This function checks if a given string (`arg`) is a valid `-n` flag, supporting both:  
- The exact `-n`.  
- Flags like `-nn`, `-nnnn`, etc., which are common in GNU-compatible `echo`.

---

**How It Works**  
1. If the `arg` is `NULL` or doesn’t start with `-n`, return `0` (not a valid `-n` flag).  
2. Ensures the first two characters are exactly `-n` using `ft_strncmp`.  
3. Starts checking from index `2` (immediately after `-n`) and loops through additional `n` characters.  
4. Returns `1` if it reaches the end of the string (`\0`), confirming a valid `-n` flag.  
5. Returns `0` if any non-`n` character is found.

---

**Why It’s Useful**  
- Modularizes flag checking for reusability and testability.  
- Handles both simple and complex `-n` flag cases efficiently.

---

### Main Function: `echo`

**Purpose**  
Implements the behavior of the `echo` command:  
- Prints arguments separated by spaces.  
- By default, appends a newline unless the `-n` flag is used.

---

**How It Works**  
1. **Initialization**:  
   - Tracks the index of the current argument (`args[i]`).  
   - Initializes `print_newline` to `1` (true).  

2. **Flag Parsing**:  
   - Iterates through arguments starting from `args[1]`.  
   - Calls `check_if_arg_minus_n` for each argument:  
     - If valid, sets `print_newline` to `0` (disable newline) and increments `i`.  
   - Stops at the first non-`-n` argument.  

3. **Argument Printing**:  
   - Loops through remaining arguments:  
     - Prints the current argument using `ft_putstr_fd`.  
     - Prints a space between arguments if more exist.  

4. **Newline Management**:  
   - Appends a newline if `print_newline` is still `1`.  

5. **Return Value**:  
   - Returns success upon completion.

---

**Behavior Examples**

| Command                  | Output        |
|--------------------------|---------------|
| `echo hello world`       | `hello world\n` |
| `echo -n hello world`    | `hello world` |
| `echo -nn hello world`   | `hello world` |
| `echo -n -n hello world` | `hello world` |

---

**Complexity Analysis**  
- **Space Complexity**: `O(1)`  
- **Time Complexity**:  
  - Best Case: `O(1)` (one short argument, no `-n` flag).  
  - Worst Case: `O(m * k)`  
    - `m`: Number of arguments.  
    - `k`: Average length of arguments.

---

**Real-World Considerations**  
- Efficient for typical shell usage.  
- Handles edge cases with long inputs or multiple flags robustly.

---

## PWD

### Auxiliary Function: `malloc_pwd`

**Purpose**  
Dynamically allocates memory to store the current working directory with flexibility and error handling.

---

**How It Works**  
1. **Initial Buffer Allocation**:  
   - Starts with a buffer size of 1024 bytes.  
   - Allocates memory using `gc_allocate`.  

2. **Directory Retrieval**:  
   - Calls `getcwd(buffer, chars)` to fetch the directory path.  
   - Returns the buffer if successful.

3. **Buffer Resizing**:  
   - If `getcwd()` fails with `errno == ERANGE`, doubles the buffer size and retries.  
   - Stops when the path fits or the maximum size (`PATH_MAX * 8`) is reached.  

4. **Error Handling**:  
   - On other errors (e.g., permission issues), deallocates memory and returns `NULL`.  

---

**Return Value**  
- The buffer containing the directory path if successful.  
- `NULL` on error or if the buffer exceeds the maximum size.

---

### Main Function: `pwd`

**Purpose**  
Implements the `pwd` command, displaying the current working directory or reporting errors.

---

**How It Works**  
1. **Initialization**:  
   - Marks arguments as unused to suppress warnings.  

2. **Directory Retrieval**:  
   - Calls `malloc_pwd`.  
   - Prints an error and exits with `EXIT_FAILURE` if retrieval fails.

3. **Output**:  
   - Prints the directory to `stdout` using `ft_putendl_fd`.  

4. **Memory Cleanup**:  
   - Deallocates memory if needed.

---

**Behavior Examples**

| Command         | Output                                   |
|------------------|-----------------------------------------|
| `pwd`           | `/home/user`                            |
| `pwd` (error)   | `Error: Failed to get current working directory.` |

---

**Complexity Analysis**  
- **Space Complexity**: `O(n)` (length of the directory path).  
- **Time Complexity**:  
  - Best Case: `O(1)` (sufficient initial buffer).  
  - Worst Case: `O(log n)` (due to resizing).

---

**Real-World Considerations**  
- Efficient for most scenarios with dynamic buffer resizing.  
- Handles deep directory structures robustly.  
- Reports issues clearly for better user experience.

---

## Summary

The implementations of `echo` and `pwd` in the mini-shell project prioritize:  
- **Flexibility**: Handles various input cases dynamically.  
- **Efficiency**: Optimized for typical shell usage.  
- **Error Handling**: Graceful reporting of issues to maintain robustness.
