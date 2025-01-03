/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:44:38 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 19:23:36 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static t_command	*create_command_node_data(char **argv,
	t_token *redirections, int type)
{
	t_command	*new_node;

	new_node = gc_allocate(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->argv = argv;
	new_node->redir = redirections;
	new_node->type = type;
	new_node->argc = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->root = NULL;
	new_node->fd[0] = -1;
	new_node->fd[1] = -1;
	return (new_node);
}

t_command	*create_command_node(t_token *tokens, t_ms *minishell)
{
	t_token	*redirections;
	char	**argv;

	redirections = ft_generate_redirs(&tokens, minishell);
	argv = build_argument_vector(tokens, minishell);
	return (create_command_node_data(argv, redirections, WORD));
}

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
