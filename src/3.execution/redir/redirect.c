/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:48:54 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 20:58:16 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	process_single_redirection(
	t_token **token_list,
	t_token **redirs,
	t_token *redir_op,
	t_ms *minishell)
{
	t_token		*redir_target;
	char		*expanded_filename;

	redir_target = redir_op->next;
	if (!redir_target || redir_target->type != WORD)
	{
		return (-1);
	}
	expanded_filename = expansor(redir_target->content, minishell);
	if (!expanded_filename)
	{
		return (-1);
	}
	redir_append_node(redirs, redir_op->type, expanded_filename);
	remove_token_from_list(token_list, &redir_op);
	remove_token_from_list(token_list, &redir_target);
	return (0);
}

t_token	*ft_generate_redirs(t_token **token_list, t_ms *minishell)
{
	t_token	*redirs;
	t_token	*current;

	redirs = NULL;
	current = *token_list;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == APPEND || current->type == HEREDOC)
		{
			if (process_single_redirection(token_list, &redirs,
					current, minishell) < 0)
				break ;
			current = *token_list;
		}
		else
		current = current->next;
	}
	return (redirs);
}
