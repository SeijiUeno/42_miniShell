/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:52:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

// Count the number of command arguments before a pipe
static int count_command_arguments(t_token *tokens) {
    int arg_count = 0;
    
    while (tokens && tokens->type != PIPE) {
        if (tokens->type == WORD) {
            arg_count++;
        }
        tokens = tokens->next;
    }
    
    return arg_count;
}

// Safely free a partially allocated argument array
static void free_argument_array_partially(char **argv, int used) {
    while (used--) {
        free(argv[used]);
    }
    free(argv);
}

// Allocate and populate an argument array with expanded variables and quotes
static char **allocate_argument_array(t_token *tokens, t_minishell *minishell, int count) {
    char **argv = malloc(sizeof(char*) * (count + 1));
    int index = 0;
    
    if (!argv) {
        return NULL;
    }
    
    while (tokens && tokens->type != PIPE) {
        if (tokens->type == WORD) {
            argv[index] = expand_vars_and_quotes(tokens->content, minishell);
            
            if (!argv[index]) {
                free_argument_array_partially(argv, index);
                return NULL;
            }
            
            index++;
        }
        tokens = tokens->next;
    }
    
    argv[index] = NULL;
    return argv;
}

// Build an argument vector from tokens
static char **build_argument_vector(t_token *tokens, t_minishell *minishell) {
    int count = count_command_arguments(tokens);
    
    if (!count) {
        return NULL;
    }
    
    return allocate_argument_array(tokens, minishell, count);
}

// Create a new command node with the given data
static t_command *create_command_node_data(
    char **argv, 
    t_token *redirections, 
    int type
) {
    t_command *new_node = malloc(sizeof(t_command));
    
    if (!new_node) {
        return NULL;
    }
    
    new_node->argv = argv;
    new_node->redir = redirections;
    new_node->type = type;
    
    // Initialize other fields to default values
    new_node->argc = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->root = NULL;
    new_node->fd[0] = -1;
    new_node->fd[1] = -1;
    
    return new_node;
}

// Create a command node with arguments and redirections
static t_command *create_command_node(
    t_token *tokens, 
    t_minishell *minishell
) {
    // Extract and remove redirections from tokens
    t_token *redirections = ft_generate_redirs(&tokens, minishell);

    // Build argument vector (now without redirection tokens)
    char **argv = build_argument_vector(tokens, minishell);

    // Create and return the command node
    return create_command_node_data(argv, redirections, WORD);
}

// Create a pipe node connecting two commands
static t_command *create_pipe_node(
    t_command *left_cmd, 
    t_command *right_cmd
) {
    // Create a pipe node with a simple "|" argv
    t_command *pipe_node = create_command_node_data(
        ft_split("|", ' '), 
        NULL, 
        PIPE
    );
    
    if (!pipe_node) {
        return NULL;
    }
    
    // Set child and root relationships
    pipe_node->left = left_cmd;
    pipe_node->right = right_cmd;
    
    if (left_cmd) {
        left_cmd->root = pipe_node;
    }
    
    if (right_cmd) {
        right_cmd->root = pipe_node;
    }
    
    return pipe_node;
}

// Move tokens to the next pipe or end of list
static void advance_to_next_pipe(t_token **tokens) {
    while (*tokens && (*tokens)->type != PIPE) {
        *tokens = (*tokens)->next;
    }
}

// Build a pipeline Abstract Syntax Tree (AST)
static t_command *build_pipeline_ast(
    t_minishell *minishell, 
    t_command *root_cmd
) {
    t_token *tokens = minishell->tokens;
    
    advance_to_next_pipe(&tokens);
    
    while (tokens) {
        if (tokens->type == PIPE) {
            // Move to the next token after the pipe
            tokens = tokens->next;
            
            if (!tokens) {
                break;
            }
            
            // Create a new command node
            t_command *new_cmd = create_command_node(tokens, minishell);
            
            if (!new_cmd) {
                return root_cmd;
            }
            
            // Create a pipe node connecting previous and new commands
            t_command *pipe_node = create_pipe_node(root_cmd, new_cmd);
            
            if (!pipe_node) {
                return root_cmd;
            }
            
            // Update root to the new pipe node
            root_cmd = pipe_node;
            
            // Advance to the next pipe
            advance_to_next_pipe(&tokens);
        } else {
            tokens = tokens->next;
        }
    }
    
    return root_cmd;
}

// Generate the Abstract Syntax Tree for the minishell
void generate_ast(t_minishell *minishell) {
    // Handle empty token list
    if (!minishell->tokens) {
        minishell->tree_cmd = NULL;
        return;
    }
    
    // Create the first command node
    t_command *first_cmd = create_command_node(minishell->tokens, minishell);
    
    if (!first_cmd) {
        minishell->tree_cmd = NULL;
        return;
    }
    
    // Build the full pipeline AST
    minishell->tree_cmd = build_pipeline_ast(minishell, first_cmd);
    
    // Debug print the generated tree
    debug_print_tree(minishell->tree_cmd, 3);
}