/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:44:38 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:21:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Create a new command node with the given data
static t_command	*create_command_node_data(char **argv,
	t_token *redirections, int type)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
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
	return (new_node);
}

/**
 * Creates a new command node using tokens.
 * @param tokens - The token list.
 * @param minishell - The shell context.
 * @return A pointer to the command node or NULL on failure.
 */
t_command	*create_command_node(t_token *tokens, t_ms *minishell)
{
	t_token	*redirections;
	char	**argv;

	redirections = ft_generate_redirs(&tokens, minishell);
	argv = build_argument_vector(tokens, minishell);
	return (create_command_node_data(argv, redirections, WORD));
}

/**
 * Creates a pipe node connecting two commands.
 * @param left_cmd - The left command node.
 * @param right_cmd - The right command node.
 * @return A pointer to the pipe node or NULL on failure.
 */
t_command	*create_pipe_node(t_command *left_cmd, t_command *right_cmd)
{
	t_command	*pipe_node;

	pipe_node = create_command_node_data(ft_split("|", ' '), NULL, PIPE);
	if (!pipe_node)
		return (NULL);
	pipe_node->left = left_cmd;
	pipe_node->right = right_cmd;
	if (left_cmd)
		left_cmd->root = pipe_node;
	if (right_cmd)
		right_cmd->root = pipe_node;
	return (pipe_node);
}
