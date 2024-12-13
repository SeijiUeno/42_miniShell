/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 20:34:20 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

/**
 * Generates the AST for the minishell.
 * @param minishell - The shell context.
 */
void generate_ast(t_minishell *minishell)
{
    if (!minishell->tokens)
    {
        minishell->tree_cmd = NULL;
        return;
    }
    t_command *first_cmd = create_command_node(minishell->tokens, minishell);
    if (!first_cmd)
    {
        minishell->tree_cmd = NULL;
        return;
    }
    minishell->tree_cmd = build_pipeline_ast(minishell, first_cmd);
    debug_print_tree(minishell->tree_cmd, 3);
}

/**
 * Builds the pipeline AST by connecting commands with pipe nodes.
 * @param minishell - The shell context.
 * @param root_cmd - The initial root command.
 * @return The updated root command or NULL on failure.
 */
t_command *build_pipeline_ast(t_minishell *minishell, t_command *root_cmd)
{
    t_token *tokens = minishell->tokens;
    advance_to_next_pipe(&tokens);
    while (tokens)
    {
        if (tokens->type == PIPE)
        {
            tokens = tokens->next;
            if (!tokens)
                break;
            t_command *new_cmd = create_command_node(tokens, minishell);
            if (!new_cmd)
                return root_cmd;
            t_command *pipe_node = create_pipe_node(root_cmd, new_cmd);
            if (!pipe_node)
                return root_cmd;
            root_cmd = pipe_node;
            advance_to_next_pipe(&tokens);
        }
        else
            tokens = tokens->next;
    }
    return root_cmd;
}
