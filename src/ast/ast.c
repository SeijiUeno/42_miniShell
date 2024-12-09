/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:48:17 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int count_args(t_token *tokens)
{
    int count = 0;
    t_token *current = tokens;

    while (current && current->type != PIPE)
    {
        if (current->type == WORD)
            count++;
        current = current->next;
    }
    return count;
}

char **generate_argv(t_token *tokens, t_minishell *minishell)
{
    int arg_count;
    char **argv;
    t_token *current;
    int index;

    arg_count = count_args(tokens);
    if (arg_count == 0)
        return NULL;

    argv = (char **)ft_calloc(arg_count + 1, sizeof(char *));
    if (!argv)
        return NULL;

    current = tokens;
    index = 0;
    while (current && current->type != PIPE)
    {
        if (current->type == WORD)
            // WIP: argv[index++] = expand_vars_and_quotes(current->content, minishell);
        current = current->next;
    }
    argv[index] = NULL;
    return argv;
}

t_token *find_last_pipe(t_token *tokens)
{
    t_token *current = tokens;
    t_token *last_pipe = tokens;

    while (current)
    {
        if (current->type == PIPE)
            last_pipe = current;
        current = current->next;
    }
    return last_pipe;
}

t_token *find_previous_pipe(t_token *token, t_minishell *minishell)
{
    t_token *current;

    if (!token)
        return NULL;

    current = token;
    while (current)
    {
        if (current->type == PIPE)
            return current;
        current = current->prev;
    }
    return minishell->tokens;
}

t_command *new_tree_node(char **args)
{
    t_command *node = gc_allocate(sizeof(t_command));
    if (!node)
        return NULL;

    node->argv = args;
    node->argc = 0;
    node->type = -1;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->redir = NULL;
    return node;
}

t_command *generate_command_node(t_token *token, t_minishell *minishell)
{
    t_command *new_node = new_tree_node(NULL);
    if (!new_node)
        return NULL;

    new_node->argv = generate_argv(token, minishell);
    // WIP: new_node->redir = generate_redirs(&token, minishell); // Use original function name
    new_node->type = WORD;
    return new_node;
}

t_command *generate_pipe_node(t_token *token, t_minishell *minishell)
{
    t_command *new_node = new_tree_node(NULL);
    if (!new_node)
        return NULL;

    new_node->argv = gc_split("|", ' '); // Keep original behavior
    new_node->type = PIPE;
    new_node->right = generate_command_node(token->next, minishell);
    if (new_node->right)
        new_node->right->parent = new_node;
    return new_node;
}

void tree_add_on_left(t_command **tree_root, t_command *new_node)
{
    t_command *current;

    if (!tree_root || !new_node)
        return;

    if (!*tree_root)
    {
        *tree_root = new_node;
    }
    else
    {
        current = *tree_root;
        while (current->left)
            current = current->left;
        current->left = new_node;
        new_node->parent = current;
    }
}

void generate_tree(t_minishell *minishell)
{
    t_token *current;
    t_command *node;

    current = find_last_pipe(minishell->tokens);
    while (current)
    {
        if (current->type == PIPE)
        {
            node = generate_pipe_node(current, minishell);
            tree_add_on_left(&minishell->tree_cmd, node);
        }
        else
        {
            node = generate_command_node(current, minishell);
            tree_add_on_left(&minishell->tree_cmd, node);
            break;
        }
        current = find_previous_pipe(current->prev, minishell);
    }
}
