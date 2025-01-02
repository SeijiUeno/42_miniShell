/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 11:15:47 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Check if the first token is an invalid leading pipe
static int	check_leading_pipe(t_token *token)
{
	char	*error_msg;

	if (!token || !token->content)
		return (0);
	error_msg = "syntax error near unexpected token `|'";
	if (token && token->content[0] == '|')
		return (error("ERROR:", error_msg, -1));
	return (0);
}

static int	check_consecutive_operators(t_token *current)
{
	char	*error_msg;

	if (!current)
		return (0);
	if (current->type == PIPE)
	{
		if (!current->next)
		{
			error_msg = "trailing operator ";
			return (error(error_msg, current->content, -1));
		}
		else if (current->next->type == PIPE)
		{
			error_msg = "consecutive operators ";
			return (error(error_msg, current->next->content, -1));
		}
	}
	return (0);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*current;
	char	*error_msg;

	current = tokens;
	if (check_leading_pipe(current))
		return (1);
	while (current)
	{
		if (check_consecutive_operators(current))
			return (1);
		current = current->next;
	}
	current = tokens;
	while (current->next)
		current = current->next;
	if (is_redirection(current->type) || current->type == PIPE)
	{
		error_msg = "syntax error near unexpected end of input";
		return (error("ERROR:", error_msg, -1));
	}
	return (EXIT_SUCCESS);
}

int	is_redirection(int token_type)
{
	return (token_type == REDIR_IN
		|| token_type == REDIR_OUT
		|| token_type == APPEND
		|| token_type == HEREDOC);
}
