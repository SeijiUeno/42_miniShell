#include "../parser.h"

static int count_args(t_token *tokens) {
    int word_count = 0;
    t_token *current = tokens;

    while (current && current->type != PIPE) {
        if (current->type == WORD) {
            word_count++;
        }
        current = current->next;  // Only advance once per iteration.
    }
    return word_count;
}

char	**ft_generate_argv(t_token *tokens, t_minishell *minishell)
{
    // WIP
}

t_ast *ft_newtreenode(char **args) {
    t_ast *new_node = malloc(sizeof(t_ast));

    if (new_node == NULL) {
        return NULL;  // Allocation failed.
    }

    new_node->argv = args;
    new_node->argc = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->type = -1;
    new_node->parent = NULL;

    // Count arguments if `args` is not NULL.
    while (args != NULL && args[new_node->argc] != NULL) {
        new_node->argc++;
    }

    return new_node;
}


void ft_treeaddonleft(t_ast **treenode, t_ast *treenew) {
    t_ast *current;

    if (treenode == NULL || treenew == NULL) {
        return;  // Invalid input.
    }
    if (*treenode == NULL) {
        *treenode = treenew;  // Set the new node as the root.
        return;
    }
    current = *treenode;
    while (current->left != NULL) {
        current = current->left;  // Traverse to the leftmost node.
    }
    current->left = treenew;
    treenew->parent = current;
}

void ft_treeaddonright(t_ast **treenode, t_ast *treenew) {
    t_ast *current;

    if (treenode == NULL || treenew == NULL) {
        return;  // Invalid input.
    }
    if (*treenode == NULL) {
        *treenode = treenew;  // Set the new node as the root.
        return;
    }
    current = *treenode;
    while (current->right != NULL) {
        current = current->right;  // Traverse to the rightmost node.
    }
    current->right = treenew;
    treenew->parent = current;
}


t_token *find_last_pipe(t_token *token) {
    t_token *current = token;
    t_token *last_pipe = NULL;

    while (current != NULL) {
        if (current->type == PIPE) {
            last_pipe = current;
        }
        current = current->next;
    }

    return last_pipe;  // May return NULL if no PIPE is found.
}

t_token *find_previous_pipe(t_token *token, t_minishell *minishell) {
    t_token *current = token;

    if (token == NULL) {
        return NULL;  // No token to process.
    }
    while (current != NULL) {
        if (current->type == PIPE) {
            return current;  // Found the previous PIPE.
        }
        current = current->prev;
    }
    return minishell->tokens;  // No PIPE found, return the first token.
}

// Generate a command node from the token list.
t_ast	*generate_command_node(t_token *token, t_minishell *shell) {
	t_ast	*command_node;

	command_node = create_command_node(NULL);
	if (!command_node)
		return (NULL);  // Allocation failed.

	command_node->argv = generate_argv(token, shell);
	command_node->type = WORD;
	return (command_node);
}

// Generate a pipe node and link it to the next command.
t_ast	*generate_pipe_node(t_token *token, t_minishell *shell) {
	t_ast	*pipe_node;

	pipe_node = create_command_node(NULL);
	if (!pipe_node)
		return (NULL);  // Allocation failed.

	// No need to use ft_split; just set argv with a static pipe symbol.
	pipe_node->argv = (char **)ft_calloc(2, sizeof(char *));
	if (!pipe_node->argv) {
		free(pipe_node);
		return (NULL);  // Memory allocation failed.
	}
	pipe_node->argv[0] = ft_strdup("|");
	pipe_node->type = PIPE;

	pipe_node->right = generate_command_node(token->next, shell);
	if (pipe_node->right)
		pipe_node->right->parent = pipe_node;

	return (pipe_node);
}

// Generate the abstract syntax tree (AST) for the shell commands.
void	generate_command_tree(t_minishell *shell) {
	t_token	*current_token;

	current_token = find_last_pipe(shell->tokens);
	while (current_token) {
		if (current_token->type == PIPE) {
			tree_add_left(&shell->tree_cmd,
				generate_pipe_node(current_token, shell));
		} else {
			tree_add_left(&shell->tree_cmd,
				generate_command_node(current_token, shell));
			break;
		}
		current_token = find_previous_pipe(current_token->prev, shell);
	}
}
