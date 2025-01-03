/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 20:12:03 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	generate_ast(t_ms *minishell)
{
	t_command	*first_cmd;

	if (!minishell->tokens)
	{
		minishell->tree_cmd = NULL;
		return ;
	}
	first_cmd = create_command_node(minishell->tokens, minishell);
	if (!first_cmd)
	{
		minishell->tree_cmd = NULL;
		return ;
	}
	minishell->tree_cmd = build_pipeline_ast(minishell, first_cmd);
}

t_command	*build_pipeline_ast(t_ms *minishell, t_command *root_cmd)
{
	t_token		*tokens;
	t_command	*new_cmd;
	t_command	*pipe_node;

	tokens = minishell->tokens;
	advance_to_next_pipe(&tokens);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tokens = tokens->next;
			if (!tokens)
				break ;
			new_cmd = create_command_node(tokens, minishell);
			pipe_node = create_pipe_node(root_cmd, new_cmd);
			if (!new_cmd || !pipe_node)
				return (root_cmd);
			root_cmd = pipe_node;
			advance_to_next_pipe(&tokens);
		}
		else
			tokens = tokens->next;
	}
	return (root_cmd);
}
