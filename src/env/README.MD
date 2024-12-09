# ENV Command and Environment Management for Mini-Shell Project

## Overview

The `env` command and its supporting functions manage environment variables in the mini-shell. The implementation uses a linked list (`t_env_list`) to dynamically handle environment variables, ensuring flexibility and scalability.

---

## Core Functions

### 1. **`environ_list_initializer`**

**Purpose**  
Initializes the environment variable linked list (`t_env_list`) from the global environment (`__environ`).

---

**How It Works**  
1. **Iterates Through Global Environment Variables**:  
   - Uses `__environ` to access the system's environment variables.  

2. **Parses Each Variable**:  
   - Splits each string at the `=` character into a `key` and `value`.  
   - Uses `gc_strndup` and `gc_strdup` to dynamically allocate memory for keys and values.  

3. **Adds Variables to the List**:  
   - Calls `add_env_variable` to append each key-value pair to the linked list.

4. **Stores the List**:  
   - Updates the global environment list using `environ_list_holder`.

---

**Why It’s Useful**  
- Converts static environment variables into a dynamic, modifiable structure.  
- Prepares the environment for operations like adding, removing, or retrieving variables.

---

### 2. **`environ_list_holder`**

**Purpose**  
Acts as a getter and setter for the global environment list.

---

**How It Works**  
1. **Stores a New List**:  
   - If a new environment list is provided (`new_env_list`), updates the global reference.  

2. **Frees the List**:  
   - If `to_free` is `1`, deallocates the current list and sets the reference to `NULL`.  

3. **Returns the Current List**:  
   - Allows other functions to access the global environment list.

---

**Why It’s Useful**  
- Centralizes the management of the environment list.  
- Ensures proper memory handling and avoids leaks.

---

### 3. **`add_env_variable`**

**Purpose**  
Adds a new environment variable to the linked list.

---

**How It Works**  
1. **Creates a New Node**:  
   - Dynamically allocates memory for a `t_env_list` node using `gc_allocate`.  
   - Stores the provided `key` and `value` in the new node.

2. **Appends the Node**:  
   - If the list is empty, sets the new node as the head.  
   - Otherwise, traverses the list and appends the new node to the end.

---

**Why It’s Useful**  
- Supports dynamic addition of new environment variables.  
- Handles empty and non-empty lists gracefully.

---

### 4. **`remove_env_variable`**

**Purpose**  
Removes an environment variable from the linked list.

---

**How It Works**  
1. **Searches for the Key**:  
   - Iterates through the list to find the node with a matching `key`.  

2. **Removes the Node**:  
   - Adjusts the previous node's `next` pointer to bypass the removed node.  

3. **Frees Memory**:  
   - Deallocates memory for the key, value, and the node itself using `gc_deallocate`.

---

**Why It’s Useful**  
- Dynamically removes variables without leaving dangling pointers.  
- Handles edge cases like removing the head or non-existent keys.

---

### 5. **`get_env_value`**

**Purpose**  
Retrieves the value of an environment variable by its key.

---

**How It Works**  
1. **Searches for the Key**:  
   - Iterates through the list and compares each node's `key` with the requested key.  

2. **Returns the Value**:  
   - If a match is found, returns the corresponding `value`.  
   - Returns `NULL` if the key is not found.

---

**Why It’s Useful**  
- Allows quick access to environment variables for command execution.  
- Handles cases where the variable does not exist.

---

### 6. **`free_env_list`**

**Purpose**  
Frees all memory allocated for the environment list.

---

**How It Works**  
1. **Traverses the List**:  
   - Iterates through each node, deallocating its `key`, `value`, and the node itself.

2. **Handles Empty Lists**:  
   - Safely exits if the list is already `NULL`.

---

**Why It’s Useful**  
- Prevents memory leaks by explicitly freeing all allocated memory.  
- Ensures proper cleanup during shell termination or environment reset.

---

## Key Structures and Functions

### **`t_env_list`**
The linked list structure for storing environment variables.

```c
typedef struct s_env_list {
    char                *key;   // Variable name
    char                *value; // Variable value
    struct s_env_list   *next;  // Pointer to the next variable
} t_env_list;
```

# `last_exit_status`

## Purpose

Stores and retrieves the last exit status of a shell command.

---

## How It Works

1. Maintains a static `status` variable.  
2. Updates the value if a non-`-1` argument is passed.  
3. Returns the current value of `status`.  

---

## Behavior Examples

| Function                   | Example Input               | Output or Behavior                  |
|----------------------------|-----------------------------|--------------------------------------|
| `add_env_variable`         | `key=USER, value=root`      | Adds `USER=root` to the list.        |
| `remove_env_variable`      | `key=USER`                 | Removes `USER` from the list.        |
| `get_env_value`            | `key=PATH`                 | Returns the value of `PATH`.         |
| `free_env_list`            | -                           | Frees all allocated memory.          |
| `environ_list_initializer` | -                           | Initializes the list from `__environ`.|

---

## Complexity Analysis

### Space Complexity
- **`O(n)`**: Proportional to the number of environment variables.

### Time Complexity
- `add_env_variable`: **`O(n)`** for appending.  
- `remove_env_variable`: **`O(n)`** for searching.  
- `get_env_value`: **`O(n)`** for searching.  
- `free_env_list`: **`O(n)`** for traversal.

---

## Real-World Considerations

### Dynamic Management
- Handles the addition and removal of variables efficiently, adapting to shell operations.

### Error Handling
- Gracefully handles invalid inputs and empty lists.

### Memory Safety
- Uses garbage collector functions (`gc_allocate` and `gc_deallocate`) to minimize memory leaks.

---

## Summary

The `last_exit_status` function and its related environment management functions provide a flexible and efficient approach for handling environment variables:

- **Linked List Structure**: Dynamically adjusts to changes in the environment.  
- **Core Functionalities**: Supports initialization, retrieval, addition, removal, and cleanup of variables.  
- **Robustness**: Handles errors and edge cases gracefully.  
- **Efficiency**: Optimized for typical shell operations.
